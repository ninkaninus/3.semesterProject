clear all

snap = audioread('Test_Generator_Snap.ogg');
smooth = audioread('Test_Generator_Smooth.ogg');
triangle = audioread('Test_Generator_Triangle.ogg');
steep40 = audioread('Test_Generator_Steep_40.ogg');
steep30 = audioread('Test_Generator_Steep_30.ogg');
steep20 = audioread('Test_Generator_Steep_20.ogg');
steep10 = audioread('Test_Generator_Steep_10.ogg');
steep5 = audioread('Test_Generator_Steep_5.ogg');
steep2_5 = audioread('Test_Generator_Steep_2.5.ogg');
steep1_25 = audioread('Test_Generator_Steep_1.25.ogg');
steep1 = audioread('Test_Generator_Steep_1.ogg');
steep0_5 = audioread('Test_Generator_Steep_0.5.ogg');
steep75 = audioread('Test_Generator_Steep_75.ogg');
steep100 = audioread('Test_Generator_Steep_100.ogg');
steep200 = audioread('Test_Generator_Steep_200.ogg');

figure(1);

subplot(3,1,1);
plot(snap);
title('Snap');

subplot(3,1,2);
plot(triangle);
title('Triangle');

subplot(3,1,3);
plot(smooth);
title('Smooth');

figure(2);

subplot(3,3,1);
plot(steep40);
title('Steep 40%');

subplot(3,3,2);
plot(steep30);
title('Steep 30%');

subplot(3,3,3);
plot(steep20);
title('Steep 20%');

subplot(3,3,4);
plot(steep10);
title('Steep 10%');

subplot(3,3,5);
plot(steep5);
title('Steep 5%');

subplot(3,3,6);
plot(steep2_5);
title('Steep 2.5%');

subplot(3,3,7);
plot(steep1_25);
title('Steep 1.25%');

subplot(3,3,8);
plot(steep1);
title('Steep 1%');

subplot(3,3,9);
plot(steep0_5);
title('Steep 0.5%');

figure(3);

subplot(4,1,1);
plot(triangle);
title('Triangle');

subplot(4,1,2);
plot(steep75);
title('Steep 75%');

subplot(4,1,3);
plot(steep100);
title('Steep 100%');

subplot(4,1,4);
plot(steep200);
title('Steep 200%');
