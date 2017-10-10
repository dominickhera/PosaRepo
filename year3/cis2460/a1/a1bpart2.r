
boyTotal <- 0
    girlTotal <- 0
childCount <- c(0,0,0,0,0)

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

            flip[3] <- flip[2]
            flip[2] <- flip[1]
            flip[1] <- newFlip

            if (is.girl(newFlip))
            girlCount <- girlCount + 1
            else
            boyCount <- boyCount + 1

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

# Answer Questions

compareGTGandGTB <- function(reps = 100){
    hthEnv <- discreteStateEnv(hthInitState, updateHTHstate, measure = flipCount, goal = gtgGoal, terminationCount = 200)
        httEnv <- discreteStateEnv(httInitState, updateHTTstate, measure = flipCount, goal = gtbGoal, terminationCount = 200)
        gabEnv <- discreteStateEnv(httInitState, updateHTTstate, measure = flipCount, goal = gabGoal, terminationCount = 200)
        gtg <- simulation.replications(reps, discreteStateSimulation, hthEnv, resultMode = "numeric")
        gtb <- simulation.replications(reps, discreteStateSimulation, httEnv, resultMode = "numeric")	
        gab <- simulation.replications(reps, discreteStateSimulation, gabEnv, resultMode = "numeric")
        cat("gtg =", mean(gtg), "\ngtb =", mean(gtb))
        cat("\n2B GTG =", (mean(gtg)*.25), "\n2B GTH =", (mean(gtb)*.25))
}
