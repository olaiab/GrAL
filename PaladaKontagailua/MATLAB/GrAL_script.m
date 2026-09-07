datuak = readmatrix('data.csv');

Denbora_sec     = datuak(:, 1) * 0.020;
IragaziGabe     = datuak(:, 2);
Seinalea        = datuak(:, 3);
paladaKop       = datuak(:, 4);
GoiMuga         = datuak(:, 5);
BeheMuga        = datuak(:, 6);

diff_kont = [0; diff(paladaKop)];
gailurrak = find(diff_kont > 0);
gailurX = Denbora_sec(gailurrak);
gailurY = Seinalea(gailurrak)/1000;

figure('Name', 'Paladen detekzioa eta mugak', 'NumberTitle', 'off');
hold on;

plot(Denbora_sec, Seinalea/1000, 'b-', 'LineWidth', 1.8);
plot(Denbora_sec, GoiMuga/1000, 'g--', 'LineWidth', 1.2);
plot(Denbora_sec, BeheMuga/1000, 'm--', 'LineWidth', 1.2);
yline(0.2, 'k:', 'LineWidth', 1.2);

if ~isempty(gailurrak)
    plot(gailurX, gailurY, 'r^', 'MarkerFaceColor', 'r', 'MarkerSize', 8);
end

grid on;
xlabel('Denbora (s)');
ylabel('Azelerazioa (g)');
xlim([min(Denbora_sec), 1000 * 0.02]);
title(sprintf('Paladen detekzioa (Palada kopurua: %d)', max(paladaKop)));
legend('Seinalea', 'Goi Muga', 'Behe Muga', 'Indar Minimoa (0,2g)', 'Palada detektatuta', 'Location', 'northeast');

figure('Name', 'Behe paseko iragazia', 'NumberTitle', 'off');
hold on;

plot(Denbora_sec, Seinalea/1000, 'b-', 'LineWidth', 1.8);
plot(Denbora_sec, IragaziGabe/1000, ':', 'Color', [0.85, 0.45, 0.1], 'LineWidth', 1.2);

grid on;
xlabel('Denbora (s)');
ylabel('Azelerazioa (g)');
xlim([min(Denbora_sec), 1000 * 0.02]);
title('Jatorriko seinalea eta iragazitako seinalea');
legend('Iragazitako seinalea', 'Iragazi gabeko seinalea', 'Location', 'northeast');
