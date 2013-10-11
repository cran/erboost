\name{shrink.erboost.pred}
\alias{shrink.erboost.pred}
%- Also NEED an '\alias' for EACH other topic documented here.
\title{ Predictions from a shrunked erboost }
\description{
  Makes predictions from a shrunken erboost model.
}
\usage{
shrink.erboost.pred(object, 
                newdata, 
                n.trees, 
                lambda = rep(1, length(object$var.names)), 
                ...)
}

\arguments{
  \item{object}{ a \code{\link{erboost.object}} }
  \item{newdata}{ dataset for predictions }
  \item{n.trees}{ the number of trees to use }
  \item{lambda}{ a vector with length equal to the number of variables containing the shrinkage parameter for each variable }
  \item{\dots}{ other parameters (ignored) }
}

\value{
A vector with length equal to the number of observations in newdata containing the predictions
}

\author{ Yi Yang \email{yiyang@umn.edu} and Hui Zou \email{hzou@stat.umn.edu} }

\section{Warning}{This function is experimental}

\seealso{ \code{\link{shrink.erboost}}, \code{\link{erboost}} }
\keyword{ methods }
