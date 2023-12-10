
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

``` r
ftmp <- tempfile(fileext = "png")
tmp <- tempfile(fileext = "png")
bench::mark(
    writeFPNG(fimg, ftmp),
    png::writePNG(img),
    check = FALSE
)
#> Warning: Some expressions had a GC in every iteration; so filtering is
#> disabled.
#> # A tibble: 2 × 6
#>   expression                 min   median `itr/sec` mem_alloc `gc/sec`
#>   <bch:expr>            <bch:tm> <bch:tm>     <dbl> <bch:byt>    <dbl>
#> 1 writeFPNG(fimg, ftmp)     32ms   32.9ms     23.9       16MB     5.96
#> 2 png::writePNG(img)       525ms  524.8ms      1.91     7.5MB     1.91
```
