# GOAP_AI_Harvisting_Simulation
personal research project into the working of the GOAP AI structure.

the goal of this little project of mine is to write a AI that can determine what neccesary steps need to be taken,
without me as developer telling what the order of the steps is. simulating this is the terminal. 
the AI should be able to tell me the steps it takes in a logical order to achieve its goal, that does not conflict with the restrictions i give it.
this will be done by using Goal Oriented Action Planning.

the Goal will be to earn a X amount of points in as little amount of steps.
points will be earned by "harvesting resources"(think of a game like factorio).th
a step would be for example to: move to resource spot, harvest, return to base, craft. etc.

however i am not allowed to tell witch step the AI should take in a certian order.
ei: i can not tell it to MoveToRecource->harvest->ReturnToBase.
only that it needs to earn points.



Changes i made to along the way:
Originaly i wanted th GOAP Agent to teleport along a nodegraph, but changed this to just working with Objects that are placed in a 2D plane (x,y pos).
i found this easyer in relationship to the FSM of tha AI, and makes it more easier to use this code in a differnet project.
if the GOAP agent started teleporting then the whole state of moving to became a bit invalid.




What is GOAP?
Goal Oriented Action Planning or GOAP, 
looks a lot like FSM (finite state machine), 
with the diffrence being that there are no preset transitions between the different states/actions.


but instead the states/actions each have a list of world changes and a list of world prerequisites.
the pawn controlled by the AI then checks the world state to see the situation its in, 
sends this situation to a Planner, witch keeps al the states and actions.
the planner  checks for a way to achieve the targeted goal. and then returns the plan to the controlled pawn.


The Result:

![term1](https://user-images.githubusercontent.com/45353205/150383986-8ad831b3-bb44-4ae9-abe5-3f5747fcf886.JPG)

So how did i get to this Result?
First the world itself.

The world holds the following information:

The Points of intrest(Base point & Resource point).

The Agent,

The GOAP planner,

The finite state mashine.

The GOAP Agent itself get filled with all the possible actions i shcould be able todo. (pickupTool,MineOre,DropOffOre).

During the first update, the GOAP AI goes into the FSM idleState.
Witch is wear the AI asks the planner if the Goal of the GOAP Agent wants to achieve is possible.
The planner gets all the possible actions of the GOAP agent, and the objects of the world to get the WorldState (ie, witch objects can be used by the actions).
The planner then goes throu all actions to reset them (even there worldtarget), cleans invalid action up, and makes a list of all the possible world changes.

The it will create a plan by going throu all the actions that can possibly change the world, if it finds a action that does this, it looks if the goal state is now valid.
If it is valid it returns the action.
If not it will restart its planning with all actions, except for the one it found that could do something, instead keeping the former action in a linked list.
This way it goes keeps until all combinations of actions become invalid, or it has found a linked list of actions that achieve this goal.

After this the list get back passed to the GOAP agent, now that it has a valid plan its ready to go.

![image](https://user-images.githubusercontent.com/45353205/150385795-d2c268d8-3162-44ac-bd7d-c81fd2d83eda.png)

Next up two things can happen: The Agent is in Range and can perform its action, or its out of range and has to move.
How, this gets done in the FSM, it can go from idle to Perform, or to Move.
the FSM looks at the plan of GOAP agent it got from the planner and checks the first task if its range or not.
if not in range it move the moveAction, witch alos looks at first Action of GOAP Action plan, gets the action target, and moves the agent.

![image](https://user-images.githubusercontent.com/45353205/150392759-48e344ea-0786-43f3-9215-2829e71f4b83.png)

If its in Range it moves to the PerformAction state, in witch it perfoms the first action in the plan, the action then get performed.

![image](https://user-images.githubusercontent.com/45353205/150392868-d5021c25-8fa7-4a6f-9256-77259320f0b2.png)

every action also has a bool to indicated when the is completed.
the FSM will check if the action is completed, and remove it from the planned action list, mmoving to the next action.

![image](https://user-images.githubusercontent.com/45353205/150393380-e8413567-6cdc-4bed-9383-62b8ca6f1e31.png)

![image](https://user-images.githubusercontent.com/45353205/150393466-e259f2fe-3058-4d89-a190-8ea67a752a5e.png)


Sources i used to create my little goap ai.

GOAP explained by Jeff Orkin. IA Lead of the GOAP AI in multiple games (FEAR,Stalker,..)
1: https://alumni.media.mit.edu/~jorkin/goap.html

How AI in Games Works Written by Ben Hardwidge
2:https://www.bit-tech.net/reviews/gaming/how-ai-in-games-works/3/

Goal Oriented Action Planning for a Smarter AI for Unity written by Brent Owens.
Reading his Unity Example to get started, and for bringing me on the Idea
3:https://gamedevelopment.tutsplus.com/tutorials/goal-oriented-action-planning-for-a-smarter-ai--cms-20793
