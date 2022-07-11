# dmuuid

Copyright (c) 2013-2018 brinkqiang (brink.qiang@gmail.com)

[![dmuuid](https://img.shields.io/badge/brinkqiang-dmuuid-blue.svg?style=flat-square)](https://github.com/brinkqiang/dmuuid)
[![License](https://img.shields.io/badge/license-MIT-brightgreen.svg)](https://github.com/brinkqiang/dmuuid/blob/master/LICENSE)
[![blog](https://img.shields.io/badge/Author-Blog-7AD6FD.svg)](https://brinkqiang.github.io/)
[![Open Source Love](https://badges.frapsoft.com/os/v3/open-source.png)](https://github.com/brinkqiang)
[![GitHub stars](https://img.shields.io/github/stars/brinkqiang/dmuuid.svg?label=Stars)](https://github.com/brinkqiang/dmuuid) 
[![GitHub forks](https://img.shields.io/github/forks/brinkqiang/dmuuid.svg?label=Fork)](https://github.com/brinkqiang/dmuuid)

## Build status
| [Linux][lin-link] | [Mac][mac-link] | [Windows][win-link] |
| :---------------: | :----------------: | :-----------------: |
| ![lin-badge]      | ![mac-badge]       | ![win-badge]        |

[lin-badge]: https://github.com/brinkqiang/dmuuid/workflows/linux/badge.svg "linux build status"
[lin-link]:  https://github.com/brinkqiang/dmuuid/actions/workflows/linux.yml "linux build status"
[mac-badge]: https://github.com/brinkqiang/dmuuid/workflows/mac/badge.svg "mac build status"
[mac-link]:  https://github.com/brinkqiang/dmuuid/actions/workflows/mac.yml "mac build status"
[win-badge]: https://github.com/brinkqiang/dmuuid/workflows/win/badge.svg "win build status"
[win-link]:  https://github.com/brinkqiang/dmuuid/actions/workflows/win.yml "win build status"

## Intro
dmuuid
```cpp
#include "dmuuid.h"
#include "dmformat.h"

int main(int argc, char* argv[]) {
    CUUID UUID;

    for (int i = 0; i < 10; i++)
    {
        auto id = UUID.generate();
        fmt::print("index:{} uuid:{}\n", i, id.str());
    }
    return 0;
}
```

output
```
$ ./dmuuidtest     
index:0 uuid:f8d8164c-84ec-6d4c-9cf9-3647072e17fa
index:1 uuid:a083a0b7-2d06-1347-b3fc-3f6fbfc3c009
index:2 uuid:a7879edd-c6c6-b44a-9077-b454b3b46c61
index:3 uuid:dadebd67-5504-004c-ae81-42966c4e5327
index:4 uuid:903d46fe-8771-b343-93a7-a937a0c0ad9f
index:5 uuid:d0067332-78fd-d841-9461-69580a5cfc4b
index:6 uuid:861220e3-20b2-eb4a-a0ba-830f341485bf
index:7 uuid:60f3d5e7-eb88-904b-8a13-61045d2c6706
index:8 uuid:93a00d7b-57f6-6745-8966-23b90ded9c48
index:9 uuid:754f454f-e70a-c94a-9a94-75a44252799a
```

## Contacts
[![Join the chat](https://badges.gitter.im/brinkqiang/dmuuid/Lobby.svg)](https://gitter.im/brinkqiang/dmuuid)

## Thanks
