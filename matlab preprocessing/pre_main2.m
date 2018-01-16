close all
clear all
clc



path = 'F:\PTB Database\PTB Database\ill\*.mat';
filelist=dir(path);
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

for index=160:length(filelist)
    filename = filelist(index).name;

    filename = strcat('F:\PTB Database\PTB Database\ill\',filename);
    filename='F:\PTB Database\PTB Database\health\s0275lrem.mat';
   % filename='F:\PTB Database\PTB Database\ill\s0118lrem.mat';
    load (filename)
    
      % ��sameLenSTд�����.mat
    if ~exist('15ST.mat','file')
        save('15ST.mat',sameLenST,'-mat');
    else
        tmpData=load('15ST.mat');
        tmpData=cat(1,tmpData,sameLenST);
        save('15ST.mat',tmpData,'-mat');
    end
    
    
    disp([num2str(index), filename,'Begin']);

        scsz = get(0,'ScreenSize');
        %figure('Position',[scsz(1) scsz(2) scsz(3) scsz(4)]);
    %%%===========
    indexQ = indexQ(indexQ<=10000);
    indexR = indexR(indexR<=10000);
    indexS = indexS(indexS<=10000);
    indexT = indexT(indexT<=10000);


    srcData = val(1, 1:10000);
    cleanData = pureECG(1, 1:10000);
    
    subplot(2, 1, 1);
   
    
 
    
    %plot(srcData-cleanData, 'r');     % ����Ϊԭʼ����-Ԥ�������
    plot(indexQ, srcData(indexQ), 'rs');
         hold on;
    plot(indexR, srcData(indexR), 'ro');
         hold on;
    % text(indexQ, srcData(indexQ), 'Q','Color','red');
 
    % text(indexR, srcData(indexR), 'R','Color','red');
    % text(indexS, srcData(indexS), 'S','Color','red');
    % text(indexT, srcData(indexT), 'T','Color','red');
    plot(indexS, srcData(indexS), 'r*');
         hold on;
    plot(indexT, srcData(indexT), 'r+');
         hold on;
    legend('Q','R','S','T',2)
     hold on;
   plot(srcData); %ԭʼ����
     title('PTB��ϵ�ԭʼECG����');
    hold on;
    
    subplot(2, 1, 2);
 
    plot(indexQ, cleanData(indexQ), 'rs');
       hold on;
    plot(indexR, cleanData(indexR), 'ro');
       hold on;
    plot(indexS, cleanData(indexS), 'r*');
       hold on;
    plot(indexT, cleanData(indexT), 'r+');
          hold on;
    legend('Q','R','S','T',2)
           hold on;
       plot(cleanData);  %Ԥ���������
    title('ȥ����Ƶ��У׼����Ư�ƺ��ECG����');
    hold on
    %text(indexQ, cleanData(indexQ), 'Q','Color','red'); 
    %text(indexR, cleanData(indexR), 'R','Color','red');
    %text(indexS, cleanData(indexS), 'S','Color','red');
    %text(indexT, cleanData(indexT), 'T','Color','red');

  
    
    
    pause
    close
   
end
