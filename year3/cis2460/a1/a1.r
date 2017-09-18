
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

	x <- diceSim(samples)

	for(i in 1:12)
	{
		x[i] <- (x[1]/samples)
	}
}

runSim <- function(n, sim, conv = identity)
{

}