# Chrome Dino Genetic Algorithm

A relatively simple artificial intelligence to teach a computer how to play Chrome Dino from scratch using a simple genetic algorithm.

![](dino_demo.gif)

## Installation

You will need Visual Studio 2017 on Microsoft Windows along like openFrameworks to run this project.

All necessary resources for graphics and sound have been included in resources.rar
Extract them and move them to \bin\data

### External Libraries / Dependencies

You will need to have/install the following depencies:

1. [Visual Studio 2017](https://visualstudio.microsoft.com/)
2. [openFramworks](https://openframeworks.cc/)

You will need to have/install the following external libraries:

1. [ofxGraph](https://github.com/TetsuakiBaba/ofxGraph)
2. [ofSoundPlayer](https://openframeworks.cc/ofBook/chapters/sound.html)
3. [Catch2](https://github.com/catchorg/Catch2)

Once all external libraries/dependencies have been installed, you can simply run the project.

## How To Play

Once the game is up and running, you can choose to either train the model (press '1') or play against the AI (press '2').

You must train the AI at least once in order to have an AI to play against.

### Controls

| Key      | Action                                                      |
|----------|-------------------------------------------------------------|
| `SPACE`  | Jump                                                        |
| `ESC`    | Exit the game												 |
| `m`      | Open the menu                                               |
| `r`      | Reset the game/training session                             |

## How Does It Work

Genetic algorithms are inspired by Charles Darwin's theory of natural evolution which reflects the process of natural selection. In this case, only the best scores will survive.
In order for the dinosaur to achieve the best score, it must determine the optimal time to jump. Usually there is an absolute maxima for optimization; however, there are many local maxima which we consider to be good enough.

We have three inputs: 

1. Distance to the nearest object
2. Velocity of the nearest object
3. Width of the nearest object

We will feed these inputs into an function (to be optimized) in order to return whether the dinosaur should jump or not.

### Genetic Algorithm

There are five dinosaurs being trained in each generation. Each dino has a set of four genes, one for each of the inputs and another that acts as a bias.
These genes are fed into the aforementioned function which determines when the dinosaur should jump. As such, we want to try out as many combinations of genes until we reach an optimal set of values at which the dinosaur jumps at the right time.

To do this, we use a few basic functions: 

1. Selection: we select the fittest individual from the population and allow them to continue to pass their genes to the next generations.
2. Crossover: we randomly split the genes from two parents and pass them on to their child. This is how we create new and better offspring which are added to the population.
3. Mutation: In new offspring, we may add some mutation which allows for us to determine if changing a specific trait leads to more desirable results. We dampen mutations as we get closer to a desired state.

To determine the fittest individual, we use a fitness score. In this case, we reward dinosaurs for jumping over obstacles and for achieving a higher score. We also penalize them for constantly jumping.

After many generations, we tend to get closer to a local maxima, at which point the algorithm terminates.

## Credits

[Introduction to Genetic Algorithms](https://towardsdatascience.com/introduction-to-genetic-algorithms-including-example-code-e396e98d8bf3)