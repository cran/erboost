\name{shrink.erboost}
\alias{shrink.erboost}
\title{ L1 shrinkage of the predictor variables in a erboost }
\description{
Performs recursive shrinkage in each of the trees in a erboost fit using different shrinkage parameters for each variable.
}
\usage{
shrink.erboost(object, 
           n.trees, 
           lambda = rep(10, length(object$var.names)), 
           ...)
}
\arguments{
  \item{object}{ A \code{\link{erboost.object}} }
  \item{n.trees}{ the number of trees to use }
  \item{lambda}{ a vector with length equal to the number of variables containing the shrinkage parameter for each variable }
  \item{\dots}{ other parameters (ignored) }
}
\details{
This function is currently experimental. Used in conjunction with a gradient ascent search for inclusion of variables.
}
\value{
  \item{predF}{Predicted values from the shrunken tree}
  \item{objective}{The value of the loss function associated with the predicted values}
  \item{gradient}{A vector with length equal to the number of variables containing the derivative of the objective function with respect to beta, the logit transform of the shrinkage parameter for each variable}
}
\references{ 
Y. Yang and H. Zou (2012) \dQuote{Nonparametric Multivariate Expectile Regression via ER-Boost,} submitted to \emph{Journal of Business & Economic Statistics}.

Hastie, T. J., and Pregibon, D. "Shrinking Trees." AT&T Bell Laboratories Technical Report (March 1990). \url{http://www-stat.stanford.edu/~hastie/Papers/shrinktree.ps} }
\author{ Yi Yang \email{yiyang@umn.edu} and Hui Zou \email{hzou@stat.umn.edu} }


\section{Warning}{This function is experimental.}

\seealso{ \code{\link{shrink.erboost.pred}}, \code{\link{erboost}} }
\keyword{ methods}% at least one, from doc/KEYWORDS

