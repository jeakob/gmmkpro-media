# jeakob — GMMK Pro Rev1 ISO (UK/GB) Keymap

Custom QMK firmware for the Glorious GMMK Pro Rev1 in ISO UK layout. Built on QMK mainline with VIA support.

---

## Base Layer

Standard UK ISO layout with a few ergonomic tweaks:

| Key | Default | Notes |
|-----|---------|-------|
| Sidebar top | Page Up | |
| Sidebar 2nd | Page Down | |
| Sidebar 3rd | Delete | |
| Sidebar 4th | End | |
| Print Screen | Print Screen | |
| Knob press | Play / Pause | Configurable — see toggle [FN]6 |

---

## FN Layer

Hold **FN** to activate. Keys light up to show their function:

### System

| Combo | Action | LED colour |
|-------|--------|-----------|
| FN + ESC | Reset all settings & RGB to defaults (EEPROM clear) | Dim red |
| FN + Backspace | Enter bootloader mode | Red |
| FN + B | Enter bootloader mode | Red |
| FN + N | Toggle N-key rollover (NKRO) | Yellow |
| FN + / | **Ctrl + Alt + Del** | Orange-red |
| FN + F | Ctrl+\` (Windows/Linux) / Ctrl+\ (macOS UK ISO) — terminal shortcut | White |
| FN + R | **Record macro 1** (press again to stop) | — |
| FN + P | **Play macro 1** | — |
| Knob press | **System sleep / Lock Screen** — Windows: HID sleep; macOS: Lock Screen (Cmd+Ctrl+Q). **LEDs turn off immediately** on press. | — |

### Function Keys — macOS MacBook layout

F1–F12 on the FN layer match the standard MacBook keyboard layout.

| Combo | Action | LED colour |
|-------|--------|-----------|
| FN + F1 | Screen brightness down | White |
| FN + F2 | Screen brightness up | White |
| FN + F3 | Mission Control (sends Shift+F3 — assign in System Settings) | Green |
| FN + F4 | Dictation (sends Ctrl+Shift+D — assign in System Settings) | Green |
| FN + F5 | Launchpad | Green |
| FN + F6 | — | — |
| FN + F7 | Previous track | Blue |
| FN + F8 | Play / Pause | Blue |
| FN + F9 | Next track | Blue |
| FN + F10 | Mute | Blue |
| FN + F11 | Volume down | Blue |
| FN + F12 | Volume up | Blue |

> F3 and F4 send key combos that must be assigned in **macOS System Settings → Keyboard → Keyboard Shortcuts**: set Mission Control to **Shift+F3** and Dictation to **Ctrl+Shift+D**. F6 (Focus/Do Not Disturb) has no suitable keycode and remains empty.

### Window Tiling (macOS only)

Hold **FN** and press a sidebar key to snap the focused window to a screen quarter. These only fire on macOS; on Windows/Linux the keys do nothing.

| Combo | Action | Shortcut sent | LED colour |
|-------|--------|--------------|-----------|
| FN + PgUp | Tile Top-Left Quarter | Ctrl+Alt+Cmd+[ | Orange |
| FN + PgDn | Tile Bottom-Left Quarter | Ctrl+Alt+Cmd+; | Orange |
| FN + Del | Tile Top-Right Quarter | Ctrl+Alt+Cmd+] | Orange |
| FN + End | Tile Bottom-Right Quarter | Ctrl+Alt+Cmd+' | Orange |

> Set matching shortcuts in **System Settings → Desktop & Dock → Windows → Quarters**.

### RGB Controls

| Combo | Action | LED colour |
|-------|--------|-----------|
| FN + Q | Saturation − | Cyan |
| FN + W | Brightness + | Cyan |
| FN + E | Saturation + | Cyan |
| FN + A | Hue − | Cyan |
| FN + S | Brightness − | Cyan |
| FN + D | Hue + | Cyan |
| FN + Z | Toggle night mode (all LEDs off; idle timeout capped at 1 min while active) | Purple |
| FN + Up | Next RGB effect | Purple-blue |
| FN + Down | Previous RGB effect | Purple-blue |
| FN + Left | Animation speed − | Purple-blue |
| FN + Right | Animation speed + | Purple-blue |
| FN + Enter (hold) | Fine RGB control layer | — |

### RGB Idle Timeout

| Combo | Action | LED colour |
|-------|--------|-----------|
| FN + − | Timeout − | Yellow |
| FN + = | Timeout + | Yellow |
| FN + Knob (rotate) | Timeout −/+ | — |

While FN is held, **F1 through F(N) light up in bright cyan** to show the current timeout level — e.g. 6 cyan F-keys = index 6 = 15 minutes.

Timeout steps: disabled → 1 → 2 → 3 → 5 → 10 → **15** → 20 → 30 → 60 minutes. Default is 15 minutes.

### Toggle Settings

| Combo | Setting | Default |
|-------|---------|---------|
| FN + `` ` `` | Print all current settings (types into focused window) | — |
| FN + 1 | CapsLock RGB — alpha keys light up green when CapsLock is on | **ON** |
| FN + 3 | ESC double-tap — tap ESC twice quickly to jump to base layer | **ON** |
| FN + 4 | Swap DEL → HOME — sidebar DEL sends Home instead of Delete | OFF |
| FN + 5 | LShift double-tap — double-tap Left Shift to toggle CapsLock | OFF |
| FN + 6 | Encoder button mode — play/pause (ON) vs mute (OFF) | **ON** |
| FN + 7 | Insert key source — Shift+Backspace = Insert (ON) vs Shift+Delete = Insert (OFF) | OFF |
| FN + 9 | AutoCorrect — 209-entry dictionary (English + Polish ASCII) | **ON** |
| FN + 0 | CapsLock extended — also highlights the `#` key green when CapsLock is on | OFF |

All toggle settings survive power cycles (stored in EEPROM).

---

## Rotary Encoder (Knob)

### Base layer — modifier held

Hold a modifier while turning the knob to change its function:

| Modifier held | Turn left | Turn right |
|--------------|-----------|------------|
| *(none)* | Volume down | Volume up |
| Right Shift | Page Down | Page Up |
| Left Ctrl | Word left (Ctrl+←) | Word right (Ctrl+→) |
| Right Ctrl | RGB hue − | RGB hue + |
| Left Alt | Undo (OS-aware) | Redo (OS-aware) |
| Win / Cmd | Previous track | Next track |
| Left Shift | Brightness − | Brightness + |

### Exponential volume

When turning without a modifier, consecutive turns in the same direction accelerate:

- **Volume up:** 1 → 2 → 4 → 8 taps (doubles each streak, max 8)
- **Volume down:** 1 → 3 → 9 taps (triples each streak, max 9)

A streak resets if you pause for more than 600 ms or reverse direction.

Encoder turns reset the RGB idle timer — turning the knob counts as activity.

### FN layer

| Action | Turn left | Turn right |
|--------|-----------|------------|
| FN held | RGB timeout − | RGB timeout + |

### Knob press

| Context | Action |
|---------|--------|
| Base layer | Play / Pause *(or Mute — see toggle [FN]6)* |
| FN held | System sleep (Windows) / Lock Screen Cmd+Ctrl+Q (macOS) — LEDs off immediately |

> **macOS sleep note:** Apple Silicon Macs and macOS 13+ do not respond to any external USB keyboard HID sleep keycode. `FN + knob press` sends **Lock Screen** (`Cmd+Ctrl+Q`) as the closest substitute — the screen locks immediately and the system can sleep on its own idle timer.
>
> For **true system sleep** from the keyboard, do this once in macOS:
> 1. Open **System Settings → Keyboard → Keyboard Shortcuts → App Shortcuts**
> 2. Click **+**, set Application to **All Applications**, Menu Title to **Sleep** (exact text, capital S), and assign a shortcut, e.g. `Ctrl+Option+Cmd+S`
> 3. In **VIA**, remap `FN + knob press` to that exact combo

---

## RGB Indicators (Left-Side Underglow)

| LED position | Colour | Meaning |
|-------------|--------|---------|
| Top (LED 1) | Red | Scroll Lock active |
| 2nd (LED 2) | Purple | Night mode on *(only visible while FN is held)* |
| 3rd (LED 3) | Green | Caps Lock active |

---

## RGB Idle Timeout

After the configured period of inactivity the LEDs turn off automatically. Any keypress wakes them instantly.

This is the recommended workaround for **macOS**, which does not suspend USB when the display sleeps (unlike Windows which cuts USB power on system sleep).

Set the timeout to match your display sleep time in System Settings so both go dark together.

---

## OS Auto-Detection

On plug-in the firmware detects the host OS and adjusts automatically:

| OS | Effect |
|----|--------|
| macOS / iOS | Left Alt ↔ Left GUI swapped (so Cmd is where you expect it) |
| Windows / Linux | Standard layout, no swap |

Right Alt is **never** swapped — it remains AltGr on all platforms, which is required for Polish and other European characters.

---

## Special Key Behaviour

### UK top-left key (`` ` `` / `¬`) on macOS

Use **British - PC** as your macOS input source (System Settings → Keyboard → Input Sources). With that layout the top-left key already sends `` ` `` (backtick) unshifted and `¬` shifted — exactly what the keycap says, with no firmware intervention required.

> Do **not** use the plain "British" (Apple-style) layout — on that variant the key sends `§`/`±` and there is no reliable firmware workaround.

### Insert

| Toggle [FN]7 | Combo | Result |
|-------------|-------|--------|
| OFF (default) | Shift + Delete | Insert |
| ON | Shift + Backspace | Insert |

### Ctrl + Backspace — delete previous word

Holding **Ctrl** and pressing **Backspace** deletes the previous word on all platforms:

| OS | Keys sent | Effect |
|----|-----------|--------|
| Windows / Linux | Ctrl + Backspace | Delete word (native) |
| macOS | Option + Backspace | Delete word (macOS equivalent) |

The translation is transparent — just press Ctrl+Backspace and it does the right thing.

### Caps Word

Press **both Shift keys simultaneously** to toggle Caps Word mode. While active, every letter is capitalised and the mode cancels automatically when you type a space, punctuation (other than `-` or `_`), or any non-letter key. Useful for typing `CONSTANT_NAMES` without holding Shift.

Pressing Shift while Caps Word is active temporarily inverts the capitalisation (i.e. pressing Shift types a lowercase letter).

### Ctrl+Alt+Del

**FN + /** always sends Ctrl+Alt+Del, implemented directly in firmware so it works regardless of what VIA has stored.

---

## EEPROM & VIA

Settings and RGB configuration persist in EEPROM across power cycles.

**VIA** is supported (PID 0x5044 is in the VIA database). VIA stores its own copy of the keymap in EEPROM. After flashing new firmware, VIA's stale keymap can override the compiled layout — causing FN-layer keys to appear not to work (they fall through to the base layer and type normally).

**Fix: press FN + ESC** immediately after flashing. This is hardcoded in firmware and always triggers an EEPROM reset and keyboard reboot, even if VIA has overwritten that key position. After the keyboard restarts, VIA detects the blank EEPROM and reloads the keymap from the compiled firmware defaults.

---

## Bootloader

Two ways to enter DFU bootloader for flashing:

1. Hold **FN** then press **Backspace**
2. Hold **FN** then press **B**

Flash the `.bin` file with QMK Toolbox or `dfu-util`.

---

## Dynamic Macros

Record and replay short key sequences without any software. Macros are stored in RAM and are lost on unplug.

| Combo | Action |
|-------|--------|
| **FN + R** | Start recording macro 1 — press FN+R again to stop |
| **FN + P** | Play back macro 1 |

While recording, the Scroll Lock LED (top left indicator) flashes. Nesting is disabled (`DYNAMIC_MACRO_NO_NESTING`) to prevent accidental recursive recordings.

---

## AutoCorrect Word List

The firmware contains a custom 209-entry dictionary that corrects typos as you type. Toggle with **FN + 9**.

> **Polish note:** QMK autocorrect only supports ASCII corrections — words with Polish diacritics (ą, ę, ó, ś, ź, ż, ć, ń) cannot appear on the *right-hand* side of a correction. The Polish entries below fix typos in words whose correct spelling uses only a–z.

### English corrections

| Typo | → | Correction |
|------|---|-----------|
| :guage | → | gauge |
| :the the | → | the |
| :thier | → | their |
| :ture | → | true |
| accomodate | → | accommodate |
| acommodate | → | accommodate |
| aparent | → | apparent |
| aparrent | → | apparent |
| apparant | → | apparent |
| apparrent | → | apparent |
| aquire | → | acquire |
| becuase | → | because |
| cauhgt | → | caught |
| cheif | → | chief |
| choosen | → | chosen |
| cieling | → | ceiling |
| collegue | → | colleague |
| concensus | → | consensus |
| contians | → | contains |
| cosnt | → | const |
| dervied | → | derived |
| fales | → | false |
| fasle | → | false |
| fitler | → | filter |
| flase | → | false |
| foward | → | forward |
| frequecy | → | frequency |
| gaurantee | → | guarantee |
| guaratee | → | guarantee |
| heigth | → | height |
| heirarchy | → | hierarchy |
| inclued | → | include |
| interator | → | iterator |
| intput | → | input |
| invliad | → | invalid |
| lenght | → | length |
| liasion | → | liaison |
| libary | → | library |
| listner | → | listener |
| looses (end of word) | → | loses |
| looup | → | lookup |
| manefist | → | manifest |
| namesapce | → | namespace |
| namespcae | → | namespace |
| occassion | → | occasion |
| occured | → | occurred |
| ouptut | → | output |
| ouput | → | output |
| overide | → | override |
| postion | → | position |
| priviledge | → | privilege |
| psuedo | → | pseudo |
| recieve | → | receive |
| refered | → | referred |
| relevent | → | relevant |
| repitition | → | repetition |
| retrun | → | return |
| retun | → | return |
| reuslt | → | result |
| reutrn | → | return |
| saftey | → | safety |
| seperate | → | separate |
| singed | → | signed |
| stirng | → | string |
| strign | → | string |
| swithc | → | switch |
| swtich | → | switch |
| thresold | → | threshold |
| udpate | → | update |
| widht | → | width |
| abreviation | → | abbreviation |
| absense | → | absence |
| accidentaly | → | accidentally |
| acheive | → | achieve |
| adress | → | address |
| alhtough | → | although |
| amout | → | amount |
| annoint | → | anoint |
| arguement | → | argument |
| asignment | → | assignment |
| assistent | → | assistant |
| atribute | → | attribute |
| availble | → | available |
| awsome | → | awesome |
| basicaly | → | basically |
| beggining | → | beginning |
| begining | → | beginning |
| belive | → | believe |
| benifit | → | benefit |
| buisness | → | business |
| catagory | → | category |
| commadn | → | command |
| commited | → | committed |
| comming | → | coming |
| completly | → | completely |
| concieve | → | conceive |
| condidtion | → | condition |
| conveniant | → | convenient |
| correclty | → | correctly |
| curently | → | currently |
| databse | → | database |
| defenitely | → | definitely |
| definately | → | definitely |
| defintion | → | definition |
| dependancy | → | dependency |
| desription | → | description |
| develoment | → | development |
| diffrence | → | difference |
| disconect | → | disconnect |
| documnet | → | document |
| donwload | → | download |
| dupilcate | → | duplicate |
| durring | → | during |
| emtpy | → | empty |
| envirnoment | → | environment |
| envirnment | → | environment |
| erorr | → | error |
| excpetion | → | exception |
| existance | → | existence |
| exlpicit | → | explicit |
| exmaple | → | example |
| exprience | → | experience |
| feautre | → | feature |
| finaly | → | finally |
| foramt | → | format |
| formated | → | formatted |
| freind | → | friend |
| fuction | → | function |
| futher | → | further |
| grammer | → | grammar |
| handeld | → | handled |
| hapened | → | happened |
| hapenned | → | happened |
| humain | → | human |
| implemnt | → | implement |
| importnat | → | important |
| inptu | → | input |
| insatll | → | install |
| interace | → | interface |
| iteraion | → | iteration |
| knwledge | → | knowledge |
| lanaguage | → | language |
| maintian | → | maintain |
| managment | → | management |
| messsage | → | message |
| middlewrae | → | middleware |
| occurance | → | occurrence |
| onlcik | → | onclick |
| paramater | → | parameter |
| perfomance | → | performance |
| permision | → | permission |
| persistance | → | persistence |
| pritnf | → | printf |
| prjoect | → | project |
| probelm | → | problem |
| programing | → | programming |
| properites | → | properties |
| publci | → | public |
| pupose | → | purpose |
| quesiton | → | question |
| reccomend | → | recommend |
| referece | → | reference |
| registerd | → | registered |
| relatd | → | related |
| remvoe | → | remove |
| rendeirng | → | rendering |
| reponse | → | response |
| repositry | → | repository |
| requirment | → | requirement |
| repsitory | → | repository |
| resovle | → | resolve |
| resposne | → | response |
| retireve | → | retrieve |
| retrive | → | retrieve |
| reuqest | → | request |
| reveiw | → | review |
| reuqire | → | require |
| securty | → | security |
| serilaize | → | serialize |
| servcie | → | service |
| soucre | → | source |
| specifc | → | specific |
| statemet | → | statement |
| stoarge | → | storage |
| structre | → | structure |
| sucess | → | success |
| supprot | → | support |
| systme | → | system |
| templte | → | template |
| timoeut | → | timeout |
| trnasfer | → | transfer |
| trnasition | → | transition |
| uniqe | → | unique |
| utliity | → | utility |
| vairable | → | variable |
| verfiy | → | verify |
| visbile | → | visible |
| webapck | → | webpack |
| withouut | → | without |

### Polish ASCII corrections

Typos in Polish words whose correct spelling uses only a–z (no diacritics needed):

| Typo | → | Correction |
|------|---|-----------|
| katalgo | → | katalog |
| kataog | → | katalog |
| komputre | → | komputer |
| komputeer | → | komputer |
| progarm | → | program |
| progrma | → | program |
| internt | → | internet |
| internset | → | internet |
| platfroma | → | platforma |
| platrfoma | → | platforma |

---

## Default RGB

On first boot or after EEPROM reset:

- Effect: **Cycle Left-Right** (slow speed 10, low saturation 70)
- Brightness: 180/255 (capped to protect the AW20216S driver and reduce USB current)
