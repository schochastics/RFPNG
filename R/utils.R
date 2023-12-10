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
