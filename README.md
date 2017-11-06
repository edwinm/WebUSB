# WebUSB

WebUSB enabled LOL shield

## Chrome support

Chrome 61, released in October 2017, supports WebUSB. The idea is simple. You connect an USB device,
a popup appears and clicking it will open a website. On this site, you can change settings,
download data etcetera. It works on every operating system, there's no local software to install and it's always up to date.

Google provides instructions to build you own WebUSB device with an Arduino Leonardo.
Not all Arduino's support WebUSB, like the UNO. See the []list of supported Arduino's](https://github.com/webusb/arduino) for WebUSB support.

On this same page you can read how to change an Arduino source file to make it support USB 2.1.

For more information, you can read this [article about WebUSB](https://developers.google.com/web/updates/2016/03/access-usb-devices-on-the-web) on the Google Developer website.

## So how do you build this yourself?

You need an Arduino Leonardo, a LOL shield and the Arduino IDE.

Change to Arduino source file to support USB 2.1, as described above and upload webusb-lol.ino to
the Arduino Leonardo.

Full instructions can be found on the [WebUSB project page](https://www.hackster.io/edwin-martin/webusb-85b6bb) on hackster.io.
