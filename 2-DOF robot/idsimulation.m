

roboArm.L = [35, 35];
roboArm.offset = [0, 0];

plot(0,0,'b*');
axis([-5 60 0 20]);
hold on;

ind = 1;

delay = 0.05;
numOfSteps = 30;

path = [getLine(5,10,5,0,numOfSteps);

        getLine(5,0,7.5,0,numOfSteps);
        getLine(7.5,0,7.5,10,numOfSteps);
        getLine(7.5,10,12.5,10,numOfSteps);
        getLine(12.5,10,12.5,0,numOfSteps);
        getLine(12.5,0,7.5,0,numOfSteps);
        getLine(7.5,0,7.5,5,numOfSteps);
        getLine(7.5,5,12.5,5,numOfSteps);
        getLine(12.5,5,12.5,0,numOfSteps);
        getLine(12.5,0,15,0,numOfSteps);
        getLine(15,0,15,10,numOfSteps);
        getLine(15,10,20,10,numOfSteps);
        getLine(20,10,20,0,numOfSteps);
       getLine(20,0,15,0,numOfSteps);
       getLine(15,0,27.5,0,numOfSteps);
       getLine(27.5,0,27.5,5,numOfSteps);
       getLine(27.5,5,22.5,5,numOfSteps);
       getLine(22.5,5,22.5,10,numOfSteps);
       getLine(22.5,10,35,10,numOfSteps);
       getLine(35,10,35,5,numOfSteps);
       getLine(35,5,30,5,numOfSteps);
       getLine(30,5,35,5,numOfSteps);
       getLine(35,5,35,0,numOfSteps);
       getLine(35,0,30,0,numOfSteps);
       getLine(30,0,42.5,0,numOfSteps);
       getLine(42.5,0,42.5,5,numOfSteps);
       getLine(42.5,5,37.5,5,numOfSteps);
       getLine(37.5,5,42.5,10,numOfSteps);
       getLine(42.5,10,42.5,0,numOfSteps);
       getLine(42.5,0,45,0,numOfSteps);
       getLine(45,0,50,10,numOfSteps);
       getLine(50,10,45,10,numOfSteps);
      
        
        ];

for n = 1:length(path)
    theta = getikine(roboArm, [path(n,1), path(n,2)],'left');
    P = getfkine(roboArm, theta - roboArm.offset);
    locationX(ind) = P(1);
    locationY(ind) = P(2);
    f(ind)= theta(1);
    g(ind)= theta (2);
    ind = ind + 1;
    hold off;
    plot(locationX,locationY,'b');
    hold on;
    grid on;
    plotRobot(roboArm, theta);
    axis([-5 60 0 20]);
    pause(delay);
end