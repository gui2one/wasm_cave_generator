# wasm cave generator

My entry project into web assembly world.

Generate 2d "caves" base on random grid.
Finding "blobs" in the output using floodfill (non-recursive as browser quickly complains about call stack size). I found a nice algorithm for that here : https://lodev.org/cgtutor/floodfill.html