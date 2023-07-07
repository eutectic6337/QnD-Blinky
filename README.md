# QnD-Blinky

Over the last few days I tried my hand at slapping together something smaller (58x31mm) and less ambitious than [TNbadge](https://github.com/eutectic6337/TNbadge) (same MCU, uses only digital outputs to display something on 3x 7 segments) using EasyEDA, the in-browser circuit CAD package that ties in with JLCPCB's manufacturing and LCSC's component warehouse.

I have the beginnings of firmware written to scroll a message across the 3x 7-segment display. 7 segments limits your choice of letters - e.g. no M, W, X (among others), and some are lowercase while others uppercase. I was thinking "dc615 ... dEFcon 31 ... " (edit in a local group of your choice), and since it's the same CPU module I'm using for the real badge there's the wireless functionality to play with, if anyone's really keen.
