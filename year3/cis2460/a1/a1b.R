
diceDiff <- function()
{
	dice1 <- sample(c(1:6), 1)
	dice2 <- sample(c(1:6), 1)

	if(dice1 > dice2)
	{
		differenceVal <- (dice1 - dice2)
	}
	else
	{
		differenceVal <- (dice2 - dice1)
	}

	return(differenceVal)
}

diceDiff2 <- function(dieSide, die2Side = 0)
{

	dice1 <- sample(c(1:diceSide), 1)
	if(dice2Side == 0)
	{
		dice2 <- sample(c(1:diceSide), 1)
	}
	else
	{
		dice2 <- sample(c(1:dice2Side), 1)
	}

	if(dice1 > dice2)
	{
		differenceVal <- (dice1 - dice2)
	}
	else
	{
		differenceVal <- (dice2 - dice1)
	}

	return(differenceVal)

}