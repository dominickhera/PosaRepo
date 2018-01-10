
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

diceDiff2 <- function(dieSide, die2Side)
{

	dice1 <- sample(c(1:dieSide), 1)

	if(die2Side == 0)
	{
		dice2 <- sample(c(1:dieSide), 1)

	}
	else
	{
		dice2 <- sample(c(1:die2Side), 1)
	}

	if(dice1 > dice2)
	{
		returnVal <- (dice1 - dice2)
	}
	else
	{
		returnVal <- (dice2 - dice1)
	}

	return(returnVal)

}