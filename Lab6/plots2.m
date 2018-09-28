clear all
prompt = 'What is the file name '; filename = input(prompt,'s');
inputValues = importdata(filename);
t = inputValues(:,1); %%first column
x = inputValues(:,2); %%second column z = inputValues(:,3); %%second column
%%make z vs x plot plot(x,z);
xlabel('x position [meters]'); ylabel('z position [meters]'); title('z vs x plot');
%%make z vs t plot
figure
plot(t,z);
xlabel('t time [seconds]'); ylabel('z position [meters]'); title('z vs t plot');