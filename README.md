# pawn-plus-timer

Credits:
XCore/Zxuan
Improve code from: 4sheed (part: PPTasks_(Start/Stop)PlayerTasks)

English: (Translate)
To be honest, I have made a timer for global/player, but it still uses a lot of native samples.
So now I use 4sheed's code for the player part.

NOTE: this doesn't work with arrays. just bool/int/float

Indonesian: 
Sejujurnya saya telah membuat timer untuk global/player, tapi masih mengunakan banyak native samp.
Jadi sekarang saya mengunakan kode milik 4sheed untuk bagian player nya.

CATATAN: ini belum bisa mengunakan array. hanya bool/int/float

## Installation
Include in your code and begin using the library:

```pawn
#include <Timer.inc>
```

## Usage

### Tasks

use `task` for an automatic timer

```pawn

task Name[1000]() 
{
    // code
}
```

### Player Tasks
> [!WARNING]
> ptask can only take a parameter for `playerid`. beyond that, it doesn't work.

Use the `ptask` macro to define player-specific tasks. These run at the specified interval for each connected player.

```pawn

ptask PlayerTaskName[interval](playerid)
{
    // This task executes for each connected player every <interval> milliseconds.
}
```

### Defer / Repeat / Stop
> [!WARNING]
> For now, they can only be on the `integer`, `bool`, and `float` parameters.

```pawn
new timerr;
main()
{
    timerr = repeat ABC[2000](65, 1022.2293);
    repeat RAWR[1000](123, 23.0);
    defer defer_time[3000](123);
}

timer ABC[0](int, Float:floating) 
{
    printf("ABC %i, %f", int, floating);
}

timer RAWR[1000](ppp, Float:rawr)
{
    printf("RAWR %i, %f", ppp, rawr);
}
timer defer_time[0](arg) 
{
    printf("defer_time(%i)", arg);
    stop timerr;
}
```
## Thanks to
- [4sheed](//github.com/r4sheed) - for the player code section that improves (//github.com/r4sheed/pawn-plus-tasks)
- [IllidanS4](//github.com/IllidanS4) — for creating [PawnPlus](//github.com/IS4Code/PawnPlus), the core library behind this include.
