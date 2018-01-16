function [ new_centers, new_clusters ] = SVDclusteringfor2( Instances )


    transMatrix = feval('deletecolumn',Instances); 
    [rowt colt]=size(transMatrix);

    %���ݱ�׼������ֵ       nnnnnnnnnnnnnn������Ϊ
    indicator = feval('averageindicator',transMatrix);

    %SVD�ֽ�
    [U,S,V] = svd(indicator);% SVM�ֽ�
    left = find(U(:,1)>=0); % U�ĵ�һ������,����0Ϊһ�࣬����Ϊ����һ��
    right = find(U(:,1)<0); % ������

    new_clusters = cell(2,1);
    new_clusters{1,1} = left';
    new_clusters{2,1} = right';

    if size(new_clusters{1,1},2)==0
        new_clusters(1) = [];
    end
    if size(new_clusters{2,1},2)==0
        new_clusters(2) = [];
    end

    new_centers = zeros( 2, colt );
    for i = 1:2
        tempNum = length(new_clusters{i,1});
        temp_center = sum(Instances(new_clusters{i,1},:),1);
        new_centers(i,:) = temp_center/tempNum;
    end







    

