#!/bin/bash
echo "
                             ___,,,,,,___                             
                      ._aaw@@@@@@@@@@@@@@@@wws,.                      
                  ._wg@@@@@@@@@@@@@@@@@@@@@@@@@@gw,.                  
               .aw@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@gc.               
             _w@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@w,             
           _m@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@g,           
         _y@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@g,         
        j@@@@@@@@@@@@@@@@@P   @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@a        
      _y@@@@@@@@@@@@@@@@@P    W@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@g.      
     _m@@@@@@@@@@@@@@@@@F     l@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@m,     
    _@@@@@@@@@@@@@@@@@@f      \@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@m,    
   .m@@@@@@@@@@@@@@@@W'        @@@@^^^^^@@@@@@@@@@@@@@@P^^^^^@@@@m    
   j@@@@@@@@@@@@@@@@@'   .m    |@@@     @@@@@@@@@@@@@@P     /@@@@@L   
  _@@@@@@@@@@@@@@@@@_____m@;   \@@@\    \@@@@@@@@@@@@F     /@@@@@@@.  
  j@@@@@@@@@@@@@@@@*****@@@@    @@@|    .@@@@@@@@@@@F     /@@@@@@@@[  
  m@@@@@@@@@@@@@@@@@@@@/@@@k    @@@@     W@@@@@@@@@P     /@@@@@@@@@k  
 .@@@@@@@@@@@@@@@____/W@@@@@    \@@@     W@@@@@@@@______/@@@@@@@@@@W  
 .@@@@@@@@@@@@@*****@@@@@@@@.    @@@     V@@@@@@@******@@@@@@@@@@@@W  
  @@@@@@@@@@@W*    sWW@@@@@@\    @@@\    i@@@@@@@@@@@@@@@@@@@@@@@@@#  
  @@@@@@@@@@P     jW@@@@@@@@m    \@@j    ;@@@@W______@@@@@@@@@@@@@@E  
  ]@@@@@@@@f     j@@@@@@@@@@@i    V@@L    @@@@*****@@@@@@@@@@@@@@@@[  
  *@@@@@@@/    .y@@@@@@@@@@@@k    l@@m    l@P    /m@@@@@@@@@@@@@@@@*  
   ]@@@@@'    .m@@@@@@@@@@@@@m    \@@@    iW    /@@@@@@@@@@@@@@@@@[   
    @@@@______@@@@@@@@@@@@@@@@_____@@@k   *    /@@@@@@@@@@@@@@@@@E    
    *@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@       j@@@@@@@@@@@@@@@@@@*    
     *@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@.     j@@@@@@@@@@@@@@@@@@*     
      *4@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@k   .m@@@@@@@@@@@@@@@@@P       
        ?@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@___m@@@@@@@@@@@@@@@@W!        
         -9@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@P'         
           *9@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@P'           
             -9@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@?'             
                *9W@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@T*                
                   *?9@@@@@@@@@@@@@@@@@@@@@@@@@@V?^                   
                       '*?9W@@@@@@@@@@@@@@WT?*'                       
                              **********                              
               ___   _____   _   _       _____   _     _  
              /   | /  ___| | | | |     | ____| | |   / / 
             / /| | | |     | | | |     | |__   | |  / /  
            / / | | | |  _  | | | |     |  __|  | | / /   
           / /  | | | |_| | | | | |___  | |___  | |/ /    
          /_/   |_| \_____/ |_| |_____| |_____| |___/     

"

echo "------------ CLEANING STEERING WHEEL DRIVERS ------------"
cd ./LogitechFFDrivers
make clean

echo "----------------- CLEANING ROS PACKAGES -----------------"
cd ../ROS
catkin_make clean

echo "--------------------- DONE CLEANING ---------------------"

