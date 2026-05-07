#!/usr/bin/env python3
"""Generates autocorrect_data.h from a dictionary file.

Usage:
    python3 gen_autocorrect.py autocorrect_dict.txt autocorrect_data.h

Format: each line is "typo -> correction"
  - Typos: a-z, apostrophe, colon (colon = word break)
  - Blank lines and lines starting with # are ignored
  - Minimum typo length: 5 characters
"""

import sys
import textwrap
from typing import Any, Dict, Iterator, List, Tuple

KC_A   = 4
KC_SPC = 0x2C
KC_QUOT = 0x34

TYPO_CHARS = dict(
    [("'", KC_QUOT), (':', KC_SPC)]
    + [(chr(c), c + KC_A - ord('a')) for c in range(ord('a'), ord('z') + 1)]
)


def parse_lines(path: str) -> List[Tuple[str, str]]:
    entries = []
    seen = set()
    with open(path, 'rt', encoding='utf-8') as f:
        for lineno, raw in enumerate(f, 1):
            line = raw.strip()
            if not line or line.startswith('#'):
                continue
            parts = [p.strip() for p in line.split('->', 1)]
            if len(parts) != 2 or not parts[0]:
                sys.exit(f'Error:{lineno}: bad syntax: "{line}"')
            typo, correction = parts
            typo = typo.lower().replace(' ', ':')
            if typo in seen:
                print(f'Warning:{lineno}: duplicate typo "{typo}", skipping')
                continue
            if not all(c in TYPO_CHARS for c in typo):
                sys.exit(f'Error:{lineno}: typo "{typo}" has chars outside a-z, \', :')
            try:
                correction.encode('ascii')
            except UnicodeEncodeError:
                sys.exit(f'Error:{lineno}: correction "{correction}" has non-ASCII chars (diacritics not supported)')
            for other in seen:
                if typo in other or other in typo:
                    sys.exit(f'Error:{lineno}: "{typo}" and "{other}" are substrings of each other')
            if len(typo) < 5:
                print(f'Warning:{lineno}: typo "{typo}" is shorter than 5 chars, may false-trigger')
            seen.add(typo)
            entries.append((typo, correction))
    return entries


def make_trie(entries: List[Tuple[str, str]]) -> Dict[str, Any]:
    trie: Dict[str, Any] = {}
    for typo, correction in entries:
        node = trie
        for ch in typo[::-1]:
            node = node.setdefault(ch, {})
        node['LEAF'] = (typo, correction)
    return trie


def encode_link(link: Dict[str, Any]) -> List[int]:
    off = link['byte_offset']
    if not (0 <= off <= 0xFFFF):
        sys.exit('Error: autocorrect table too large (>64KB)')
    return [off & 255, off >> 8]


def serialize_trie(entries: List[Tuple[str, str]], trie: Dict[str, Any]) -> List[int]:
    table: List[Dict[str, Any]] = []

    def traverse(node):
        if 'LEAF' in node:
            typo, correction = node['LEAF']
            wb_end = typo[-1] == ':'
            typo = typo.strip(':')
            i = 0
            while i < min(len(typo), len(correction)) and typo[i] == correction[i]:
                i += 1
            backspaces = len(typo) - i - 1 + wb_end
            assert 0 <= backspaces <= 63, f'backspaces={backspaces} out of range for "{typo}"'
            suffix = correction[i:]
            entry = {'data': [backspaces + 128] + list(suffix.encode('ascii')) + [0],
                     'links': [], 'byte_offset': 0}
            table.append(entry)
        elif len(node) == 1:
            c, child = next(iter(node.items()))
            entry = {'chars': c, 'byte_offset': 0}
            while len(child) == 1 and 'LEAF' not in child:
                c, child = next(iter(child.items()))
                entry['chars'] += c
            table.append(entry)
            entry['links'] = [traverse(child)]
        else:
            chars = ''.join(sorted(node.keys()))
            entry = {'chars': chars, 'byte_offset': 0}
            table.append(entry)
            entry['links'] = [traverse(node[c]) for c in chars]
        return entry

    traverse(trie)

    def serialize(e):
        if not e['links']:
            return e['data']
        if len(e['links']) == 1:
            return [TYPO_CHARS[c] for c in e['chars']] + [0]
        data = []
        for c, link in zip(e['chars'], e['links']):
            data += [TYPO_CHARS[c] | (0 if data else 64)] + encode_link(link)
        return data + [0]

    off = 0
    for e in table:
        e['byte_offset'] = off
        off += len(serialize(e))
    assert off <= 0xFFFF

    return [b for e in table for b in serialize(e)]


def main():
    if len(sys.argv) < 3:
        sys.exit(f'Usage: {sys.argv[0]} <dict.txt> <output.h>')
    dict_path, out_path = sys.argv[1], sys.argv[2]

    entries = parse_lines(dict_path)
    if not entries:
        sys.exit('No entries parsed from dictionary')

    trie = make_trie(entries)
    data = serialize_trie(entries, trie)

    min_typo = min(entries, key=lambda e: len(e[0]))[0]
    max_typo = max(entries, key=lambda e: len(e[0]))[0]

    lines = [
        '#pragma once',
        f'// Autocorrection dictionary ({len(entries)} entries):',
    ]
    for typo, correction in entries:
        lines.append(f'//   {typo:<{len(max_typo)}} -> {correction}')
    lines += [
        '',
        f'#define AUTOCORRECT_MIN_LENGTH {len(min_typo)}  // "{min_typo}"',
        f'#define AUTOCORRECT_MAX_LENGTH {len(max_typo)}  // "{max_typo}"',
        f'#define DICTIONARY_SIZE {len(data)}',
        '',
        'static const uint8_t autocorrect_data[DICTIONARY_SIZE] PROGMEM = {',
        textwrap.fill('    %s' % ', '.join(f'0x{b:02X}' for b in data),
                      width=100, subsequent_indent='    '),
        '};',
    ]

    with open(out_path, 'w', encoding='utf-8') as f:
        f.write('\n'.join(lines) + '\n')

    print(f'Wrote {out_path}: {len(entries)} entries, {len(data)} bytes')


if __name__ == '__main__':
    main()
