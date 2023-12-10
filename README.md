
<!-- README.md is generated from README.Rmd. Please edit that file -->

# RFPNG

<!-- badges: start -->
<!-- badges: end -->

RFPNG wraps [fpng](https://github.com/richgel999/fpng), a very fast C++
.PNG image reader/writer for 24/32bpp images

## Installation

You can install the development version of RFPNG from
[GitHub](https://github.com/) with:

``` r
# install.packages("devtools")
devtools::install_github("schochastics/RFPNG")
```

## Example

``` r
library(RFPNG)
```

RFPNG can only read pngs that were encoded with RFPNG. For regular pngs,
use `png::readPNG`

``` r
img <- png::readPNG("bear.png")
```

<img src="bear.png" width="512">

Before writing with FPNG, the array needs to be reshaped, which includes
converting from \[0,1\] values to \[0,255\].

``` r
fimg <- reshape_to_fpng(img)
```

## Benchmark

`writeFPNG` is significantly faster than `png::writePNG`.

``` r
ftmp <- tempfile(fileext = "png")
tmp <- tempfile(fileext = "png")
bench::mark(
    writeFPNG(fimg, ftmp),
    png::writePNG(img, tmp),
    check = FALSE
)
#> # A tibble: 2 × 6
#>   expression                   min   median `itr/sec` mem_alloc `gc/sec`
#>   <bch:expr>              <bch:tm> <bch:tm>     <dbl> <bch:byt>    <dbl>
#> 1 writeFPNG(fimg, ftmp)     31.4ms   34.2ms     28.9       16MB     9.62
#> 2 png::writePNG(img, tmp)  575.6ms  575.6ms      1.74    4.02MB     0
```

same goes for the reading

``` r
bench::mark(
    readFPNG("fbear.png"),
    png::readPNG("bear.png"),
    png::readPNG("fbear.png"),
    check = FALSE
)
# A tibble: 3 × 13
#>   expression     min  median `itr/sec` mem_alloc `gc/sec` n_itr  n_gc total_time result memory
#>   <bch:expr>  <bch:> <bch:t>     <dbl> <bch:byt>    <dbl> <int> <dbl>   <bch:tm> <list> <list>
#> 1 "readFPNG(… 29.8ms  33.6ms      29.7      16MB     13.2     9     4    303.1ms <NULL> <Rprofmem>
#> 2 "png::read… 75.7ms 100.9ms      10.7      36MB     10.7     3     3    279.5ms <NULL> <Rprofmem>
#> 3 "png::read… 97.3ms  97.3ms      10.3      36MB     41.1     1     4     97.3ms <NULL> <Rprofmem>
#> # ℹ 2 more variables: time <list>, gc <list>
```
