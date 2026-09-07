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
gailurY = Seinalea(gailurrak);

% Grafikoa sortu
figure('Name', 'Paladen detekzioa goi-muga eta behe-mugarekin', 'NumberTitle', 'off');
hold on;

plot(Denbora_sec, Seinalea, 'b-', 'LineWidth', 1.8);
plot(Denbora_sec, IragaziGabe, ':', 'Color', [0.5, 0.5, 0.5], 'LineWidth', 1.8);
plot(Denbora_sec, GoiMuga, 'g--', 'LineWidth', 1.2);
plot(Denbora_sec, BeheMuga, 'm--', 'LineWidth', 1.2);

yline(1000, 'k:', 'LineWidth', 1.2);

if ~isempty(gailurrak)
    plot(gailurX, gailurY, 'r^', 'MarkerFaceColor', 'r', 'MarkerSize', 8);
end

grid on;
xlabel('Denbora (s)');
ylabel('Indarra');
xlim([min(Denbora_sec), 900 * 0.02]);
title(sprintf('Paladen detekzioa (Palada kopurua: %d)', max(paladaKop)));
legend('Seinalea', 'Goi Muga', 'Behe Muga', 'Indar Minimoa (1000)', 'Palada detektatuta', 'Location', 'northeast');
