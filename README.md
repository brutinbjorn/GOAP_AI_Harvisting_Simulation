# GOAP_AI_Harvisting_Simulation
personal research project into the working of the GOAP AI structure.

the goal of this little project of mine is to write a AI that can determine what neccesary steps need to be taken,
without me as developer telling what the order of the steps is. simulating this is the terminal. 
the AI should be able to tell me the steps it takes in a logical order to achieve its goal, that does not conflict with the restrictions i give it.
this will be done by using Goal Oriented Action Planning.

the Goal will be to earn a X amount of points in as little amount of steps.
points will be earned by "harvesting resources"(think of a game like factorio).th
certain resources wil have higher value but will require for the AI use a tool ("pickaxe for example").
a step would be for example to: move to resource spot, harvest, return to base, craft. etc.

however i am not allowed to tell witch step the AI should take in a certian order.
ei: i can not tell it to MoveToRecource->harvest->ReturnToBase.
only that it needs to earn points.


What is GOAP?
Goal Oriented Action Planning or GOAP, 
looks a lot like FSM (finite state machine), 
with the diffrence being that there are no preset transitions between the different states/actions.

but instead the states/actions each have a list of world changes and a list of world prerequisites.
the pawn controlled by the AI then checks the world state to see the situation its in, 
sends this situation to a Planner, witch keeps al the states and actions.
the planner  checks for a way to achieve the targeted goal. and then returns the plan to the controlled pawn.




Sources

GOAP explained by Jeff Orkin. IA Lead of the GOAP AI in multiple games (FEAR,Stalker,..)
1: https://alumni.media.mit.edu/~jorkin/goap.html
How AI in Games Works Written by Ben Hardwidge
2:https://www.bit-tech.net/reviews/gaming/how-ai-in-games-works/3/
