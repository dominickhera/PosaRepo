###  Load discreteStateSimulation.R before using

############################# Coin Example ################################

# helper functions
# boyTotal <- 0
# girlTotal <- 0
    childCount <- c(0,0,0,0,0)
exactChildCount <- c(0,0,0,0,0)

    girl <- function() {
        'g'
    }

boy <- function() {
    'b'
}

is.girl <- function(coinFlip) {
    !is.na(coinFlip) && coinFlip == girl()
}

is.boy <- function(coinFlip) {
    !is.na(coinFlip) && coinFlip == boy()
}

coinFlip <- function() {
    sample(c(boy(), girl()), 1)
}

# state initializors
# state is stored in an environment so state variables that hold vectors and lists will not be
# copied when passed into the updateState() function
#
# Note: while the state in the HTT/HTH problem is small enough in this case not to matter, 
#       the environment mechanism is used anyway for consistancy and as a simple example 
#       to base more complex states on.

hthInitState <- function(flip = c(NA, NA, NA), girlCount = 0, boyCount = 0) {
    flip; girlCount; boyCount
        environment()
}

# the htt initial state is identical to the hth inital state, so the creation function is just copied
httInitState <- hthInitState

# state update function

updateflip3State <- function(state){
    with(state, {
            newFlip <- coinFlip()

# flip[3] <- flip[2]
            flip[2] <- flip[1]
            flip[1] <- newFlip

            if (is.girl(newFlip))
            {
            girlCount <- girlCount + 1
            }
            else
            {
            boyCount <- boyCount + 1
            }

            })
    state
}

# the update function is the same for HTH and HTT (only the goals are different in the two cases)
updateHTHstate <- updateflip3State
updateHTTstate <- updateflip3State

# Goal

gtgGoal <- function(state) {
    with(state, {
            is.girl(flip[1]) && is.boy(flip[2]) && is.girl(flip[3])		
            })	
}

gtbGoal <- function(state) {
    with(state, {
            is.boy(flip[1]) && is.boy(flip[2]) && is.girl(flip[3])		
            })	
}

gabGoal <- function(state) {
    with(state, {
            is.boy(flip[1]) && is.girl(flip[2])
            })
}

# Measures

flipCount <- function(state) {
    with(state, girlCount + boyCount)
}

girlCount <- function(state) {
    with(state, girlCount)
}

boyCount <- function(state) {
    with(state, boyCount)
}

freq <- function(samples, size = sum(samples))
{

    x <- samples

        # xSum <- sum(x)
        for(i in 1:5)
        {
            x[i] <- ((x[i]/size)*100)
        }
    return(x)
}


# Answer Questions

compareGTGandGTB <- function(reps = 100){
    gabEnv <- discreteStateEnv(httInitState, updateHTTstate, measure = flipCount, goal = gabGoal, terminationCount = 200)
        gab <- simulation.replications(reps, discreteStateSimulation, gabEnv, resultMode = "numeric")

        for(i in 1:reps)
        {
            if(gab[i] >= 1)
            {
                childCount[1] <- childCount[1] + 1
                    if(gab[i] >= 2)
                    {
                        childCount[2] <- childCount[2] + 1
                            if(gab[i] >= 3)
                            {
                                childCount[3] <- childCount[3] + 1
                                    if(gab[i] >= 4)
                                    {
                                        childCount[4] <- childCount[4] + 1
                                            if(gab[i] >= 5)
                                            {
                                                childCount[5] <- childCount[5] + 1
                                            }
                                    }
                            }

                    }
            }

        }

    for(i in 1:reps)
    {
# cat("\ngab val =", gab[i])
        if(gab[i] == 1)
        {

            exactChildCount[1] <- exactChildCount[1] + 1
        }

        if(gab[i] == 2)
        {
            exactChildCount[2] <- exactChildCount[2] + 1
        }

        if(gab[i] == 3)
        {
            exactChildCount[3] <- exactChildCount[3] + 1
        }

        if(gab[i] == 4)
        {
            exactChildCount[4] <- exactChildCount[4] + 1

        }

        if(gab[i] == 5)
        {
            exactChildCount[5] <- exactChildCount[5] + 1
        }
    }
        averageChildCount <- c(1:reps)
        averageExactChildCount <- c(1:reps)

          for(j in 1:childCount[1])
          {
            averageChildCount[j] <- 1
          }
          
          for(j in 1:exactChildCount[1])
          {
            averageExactChildCount[j] <- 1
          }
          
          for(j in childCount[1] + 1:sum(childCount[2] + childCount[1]))
          {
            averageChildCount[j] <- 2
          }
          
          for(j in exactChildCount[1] + 1:sum(exactChildCount[2] + exactChildCount[1]))
          {
            averageExactChildCount[j] <- 2
          }
          
        for(j in childCount[1] + childCount[2] + 1: sum(childCount[1] + childCount[2] + childCount[3]))
       	{
      		averageChildCount[j] <- 3
       	}
          
         for(j in exactChildCount[1] + exactChildCount[2] + 1: sum(exactChildCount[1] + exactChildCount[2] + exactChildCount[3]))
       	{
      		averageExactChildCount[j] <- 3
       	}

       	for(j in childCount[1] + childCount[2] + childCount [3] + 1: sum(childCount[1] + childCount[2] + childCount[3] + childCount[4]))
       	{
       		averageChildCount[j] <- 4
       	}
         
        for(j in exactChildCount[1] + exactChildCount[2] + exactChildCount[3] + 1: sum(exactChildCount[1] + exactChildCount[2] + exactChildCount[3] + exactChildCount[4]))
       	{
       		averageExactChildCount[j] <- 4
       	} 

       	for(j in childCount[1] + childCount[2] + childCount[3] + childCount[4]+ 1: sum(childCount[1] + childCount[2] + childCount[3] + childCount[4] + childCount[5]))
       	{
       		averageChildCount[j] <- 5
       	}
         
        for(j in exactChildCount[1] + exactChildCount[2] + exactChildCount[3] + exactChildCount[4] + 1: sum(exactChildCount[1] + exactChildCount[2] + exactChildCount[3] + exactChildCount[4] + exactChildCount[5]))
       	{
       		averageExactChildCount[j] <- 5
       	}



    	freqChildCount <- freq(childCount)
        freqExactChildCount <- freq(exactChildCount, sum(gab))
# cat("gab =", gab)
        cat("\nchildCount =", childCount, "\nfreqChildCount =", freqChildCount)
        cat("\nexact childCount =", exactChildCount, "\nexact freqChildCount =", freqExactChildCount)
        # cat("\naverage child count = ", averageChildCount, "\naverage exact child count =", averageExactChildCount)
        cat("\naverage child count = ", mean(averageChildCount), "\naverage exact child count =", mean(averageExactChildCount))
#cat("\n2B GTG =", (mean(gtg)*.25), "\n2B GTH =", (mean(gtb)*.25))
}
