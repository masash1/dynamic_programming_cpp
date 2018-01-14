clear all;close all; clc;

fileCPU = 'refCPU';
[dataCPU,delimiterOut]=importdata(fileCPU);
fileGPU = 'refGPU';
[dataGPU,delimiterOut]=importdata(fileGPU);


figure
plot(dataCPU(:,1),dataCPU(:,2))
hold on
plot(dataGPU(:,1),dataGPU(:,2))
xlabel('Number of States')
ylabel('Time (ms)')

legend('CPU','GPU')

mdlCPU = fitlm(dataCPU(:,1),dataCPU(:,2));
mdlGPU = fitlm(dataGPU(:,1),dataGPU(:,2));

num_states=10000000;%hyakuoku
predCPU=predict(mdlCPU,num_states);
predGPU=predict(mdlGPU,num_states);
fprintf('%d states\n',num_states);
fprintf('CPU may take %f (h)\n',((predCPU/1000)/60)/60)
fprintf('GPU may take %f (h)\n',((predGPU/1000)/60)/60)
