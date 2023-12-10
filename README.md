
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

![](bear.png)

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
#> # A tibble: 2 × 6
#>   expression                 min   median `itr/sec` mem_alloc `gc/sec`
#>   <bch:expr>            <bch:tm> <bch:tm>     <dbl> <bch:byt>    <dbl>
#> 1 writeFPNG(fimg, ftmp)   31.8ms   32.6ms     30.4       16MB     13.5
#> 2 png::writePNG(img)     512.3ms  512.3ms      1.95     7.5MB      0
```
