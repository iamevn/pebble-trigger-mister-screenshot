barebones app to trigger a screenshot on the MiSTer running on local network as a [One Click Action](https://developer.rebble.io/guides/design-and-interaction/one-click-actions/)

expects MiSTer to be running [mrext's Remote extension](https://github.com/wizzomafizzo/mrext/blob/main/docs/remote.md) accessible on the local network at `http://mister:8182`

mister_kun from https://github.com/baxysquare/mister_kun
* icon converted with: `magick src/8-bit_mister_kun_bw_16x16.png -gravity center -background transparent -extent 25x25 icon.png`
* mister_kun [platform-specific resources](https://developer.rebble.io/guides/app-resources/platform-specific/) converted with:
  * `inkscape -w 240 -h 240 mister_kun_fullcolor.svg --export-filename mister_kun~260w~color.png`
  * `inkscape -w 180 -h 180 mister_kun_fullcolor.svg --export-filename mister_kun~200w~color.png`
  * `inkscape -w 160 -h 160 mister_kun_fullcolor.svg --export-filename mister_kun~180w~color.png`
  * `inkscape -w 124 -h 124 mister_kun_fullcolor.svg --export-filename mister_kun~144w~color.png`
  * `inkscape -w 124 -h 124 mister_kun_bw.svg --export-filename mister_kun~144w~bw.png`
  