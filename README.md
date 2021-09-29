# ESPHome component: nimble_beacon

A drop-in replacement for `esp32_ble_beacon` that uses `NimBLE-Arduino` stack (library) to conserve heap and code memory requirements.

Default `esp32_ble_beacon` implementation uses ESP32 Bluedroid Bluetooth implementation which has much higher heap and code memory requirements due to it being a dual stack implementation (Bluetooth Classic and Bluetooth Low Energy).

Although ESPHome conserves memory by freeing unneded Bluetooth Classic memory, the resulting memory consumption is still significantly higher than that of `NimBLE-Arduino` library.


## Configuration

This is a drop-in replacement for `esp32_ble_beacon`. Please see [ESP32 Bluetooth Low Energy Beacon](https://esphome.io/components/esp32_ble_beacon.html) for details.

Register `nimble_beacon` component in `external_components` section of your device configuration YAML:

```YAML
external_components:
  - source: github://akomelj/esphome-nimble_beacon@main
    refresh: 0s
```

Replace `esp32_ble_beacon` configuration key with `nimble_beacon`:

```YAML
# Example configuration entry
nimble_beacon:
  type: iBeacon
  uuid: 'c29ce823-e67a-4e71-bff2-abaa32e77a98'
```



## The MIT License (MIT)


Copyright © `2021` `Andrej Komelj`

Permission is hereby granted, free of charge, to any person
obtaining a copy of this software and associated documentation
files (the “Software”), to deal in the Software without
restriction, including without limitation the rights to use,
copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the
Software is furnished to do so, subject to the following
conditions:

The above copyright notice and this permission notice shall be
included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
OTHER DEALINGS IN THE SOFTWARE.