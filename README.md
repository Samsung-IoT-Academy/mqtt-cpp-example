# MQTT C++ example

Пример кода с использованием библиотеки [Paho] в версии C++.

## Компиляция

### Ubuntu

Требуются следующие предустановленные пакеты:
 * `build-essenstial`,
 * `libjsoncpp1`,
 * `libjsoncpp-dev`.

Также требутются в установленном в виде пакета или просто установленные через
`make install` следующие библиотеки:
* [paho.mqtt.c] — клиентская библиотека Eclipse Paho MQTT, версия для С,
* [paho.mqtt.c++] — клиентская библиотека Eclipse Paho MQTT, версия для С++,
* [args] — библиотека для парсинга аргументов командной строки.

Затем в директории проекта необходимо запустить сборку:
```
make INCLUDE_DIRS="-I/usr/include/jsoncpp" all
```

В директории `build-mqtt-cpp/` на уровень выше будет находиться результат сборки
в виде исполняемого файла mqtt-cpp.

## Запуск

Опции командной строки:
 * `--ip` — IP-адрес сервера.
 * `--port` — порт сервера.
 * Топики для подписки можно указывать в двух форматах:
   * `--topics` — топики в обычном формате
   * `--device` — адрес устройства, `--sensors` — датчики на устройстве.
 * `--qos` — Quality of Service (каждый номер QoS отвечает за соответствующий по
    порядку топик)


[Paho]:https://github.com/eclipse/paho.mqtt.cpp
[paho.mqtt.c]:https://github.com/eclipse/paho.mqtt.c
[paho.mqtt.c++]:https://github.com/eclipse/paho.mqtt.cpp
[args]:https://github.com/Taywee/args
