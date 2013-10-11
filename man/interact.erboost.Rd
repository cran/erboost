\name{interact.erboost}
\alias{interact.erboost}
\title{ Estimate the strength of interaction effects }
\description{ Computes Friedman's H-statistic to assess the strength of variable interactions. }
\usage{
interact.erboost(x,
             data,
             i.var = 1,
             n.trees = x$n.trees)
}
\arguments{
  \item{x}{ a \code{\link{erboost.object}} fitted using a call to \code{\link{erboost}}}
  \item{data}{ the dataset used to construct \code{x}. If the original dataset is
     large, a random subsample may be used to accelerate the computation in
     \code{interact.erboost}}
  \item{i.var}{a vector of indices or the names of the variables for compute
     the interaction effect. If using indices, the variables are indexed in the
     same order that they appear in the initial \code{erboost} formula.}
  \item{n.trees}{ the number of trees used to generate the plot. Only the first
     \code{n.trees} trees will be used}
}
\details{
\code{interact.erboost} computes Friedman's H-statistic to assess the relative
strength of interaction effects in non-linear models. H is on the scale of
[0-1] with higher values indicating larger interaction effects. To connect to
a more familiar measure, if \eqn{x_1} and \eqn{x_2} are uncorrelated covariates
with mean 0 and variance 1 and the model is of the form
\deqn{y=\beta_0+\beta_1x_1+\beta_2x_2+\beta_3x_3}
then
\deqn{H=\frac{\beta_3}{\sqrt{\beta_1^2+\beta_2^2+\beta_3^2}}}
}
\value{
Returns the value of \eqn{H}.
}
\references{
Y. Yang and H. Zou (2012) \dQuote{Nonparametric Multivariate Expectile Regression via ER-Boost,} submitted to \emph{Journal of Business & Economic Statistics}.

J.H. Friedman and B.E. Popescu (2005). \dQuote{Predictive Learning via Rule
Ensembles.} Section 8.1
}
\author{Yi Yang \email{yiyang@umn.edu} and Hui Zou \email{hzou@stat.umn.edu}}

\seealso{ \code{\link{erboost}}, \code{\link{erboost.object}} }

\keyword{ methods }
