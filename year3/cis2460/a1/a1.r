
diceSim <- function(n)
{
	rollType <- c(0,0,0,0,0,0,0,0,0,0,0,0)
	for(i in 1:n)
	{
		dice1 <- sample(c(1:6), 1)
		dice2 <- sample(c(1:6), 1)
		totalCount <- (dice1 + dice2)

		rollType[totalCount] <- (rollType[totalCount] + 1)
	}

	return(rollType)

}

freq <- function(samples)
{

	x <- samples

	xSum <- sum(x)
	for(i in 1:11)
	{
		x[i] <- (x[i]/xSum)
	}
	return(x)
}

runSim <- function(n, sim, conv = identity)
{

  ranNum <- diceSim(n)
  
  freqInfo <- freq(ranNum)
  
  return(freqInfo)
  
}