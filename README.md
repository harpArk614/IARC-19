# IARC-19

codes in this repository are for line following, wall following, and node detection designed by me and my team for IARC'19 a part of TECHKRITI'19 held in IIT KANPUR.

Problem Statement for the competition
 

You shall place your bot at point A in any direction, in order to perform line following.
In the path, there will be several nodes that may be TRUE or FALSE node. Discription of Nodes is mentioned below
Your bot shall count these TRUE nodes and display this data real-time on an LCD screen. This data can also be displayed on a mobile or laptop screen via wireless communication between both.
Bot must dispaly TRUE or FALSE for after it crosses a node, otherwise it will be treated as undetected node.
After reaching the point B by following the line, it then has to travel to another point C by following a path, bounded by a continuous wall on one side and a line running parallel to the wall on the other side at a distance of 450mm, by the principles of the wall following. In case the bot crosses the line, human intervention would be allowed and points would be cut for the same.
After reaching point C, the bot has to follow a continuous wall again, according to the same rules as mentioned above, but this time, the wall will be in the opposite direction as that of the previous one. It would then reach point D.
After reaching D it must again traverse on black lines.
Again there will be 2 TRUE nodes, your bot should measure the distance b/w two adjacent correct nodes.
Following the above directions, the bot would reach the Finish area. There it has to show the message “FINISH” then show the number of correct nodes encountered & distance b/w last two correct nodes on an LCD display.
 

NOTE:

The sequence of TRUE and FALSE nodes will be random and disclosed only during the event.
The bot will be allowed to transverse the maze part only once.
Arena
Top View

The line width of the line following part will be 3cm.
The height of the wall is 300mm.
There will be circular checkpoints A, B, C and D.
The distance between the node I_D and I_E can be anything from 90cm to 120cm.
All checkpoints (including start and end points) are circular of dimension 30cm.
Note:  The above arena is only for reference. The number and position of nodes may be different in the final arena.

Robot Control
You can start the bot at the beginning of the trial and no human intervention is allowed thereafter. If human intervention is necessary, the ongoing trial will come to an end. Teams may go for another trial if they have sufficient time left.
During wall following, a line would be drawn at a distance of 450 mm from the wall. The bot must not cross this line at any cost. In case the bot crosses the line, human intervention would be allowed and points would be deducted for the same.
The judges can ask for an explanation for any mechanism of the bot and there would be an immediate disqualification of defaulters.
Bot Specifications
​​​​​​​The bot should not be factory made or commercially built setup or pre-manufactured bots/lego bots.
During the whole event, the bot must fit within a square of 250x250x250(mm) (l x b x h).
The Robot must be stable and able to move on its own. A bot not fulfilling these criteria will be disqualified.
The bots should be able to follow the line according to event specifications.
For wall following and distance calculation between nodes, the team can use any sort of technology/sensor as far as it fits in the dimension mentioned.
Each team has to bring its own power supply for its robots. The voltage difference between any two points on the bot must not exceed 24 volts.
Teams are advised to use an onboard power supply. In case they are using external power supply they will be responsible for any problem created by entanglement of wires.
