#' Reshape png array
#' Reshape a png array that was read with [png::readPNG] to comply with fpng
#' @param x array representing a png image
#' @export
reshape_to_fpng <- function(x) {
    d <- dim(x)
    if (max(x) <= 1) {
        x <- round(x * 255)
    }
    x <- aperm(x, c(3, 2, 1))
    x <- array(c(x), c(d[1], d[2], d[3]))
    return(x)
}

#' Initialize fpng
#' run one time on startup
#' @export
fpng_init <- function() {
    init_fpng()
}

#' convert png to be compatible with fpng
#' @param png_path path to png file to be converted
#' @param fpng_path path to output png file
#' @export
png2fpng <- function(png_path, fpng_path) {
    if (!requireNamespace("png", quietly = TRUE)) {
        stop("png is needed for this function to work. Please install it.", call. = FALSE)
    }
    img <- png::readPNG(png_path)
    fimg <- reshape_to_fpng(img)
    writeFPNG(fimg, fpng_path)
    invisible(NULL)
}
