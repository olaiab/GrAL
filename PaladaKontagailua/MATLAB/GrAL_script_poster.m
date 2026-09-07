datuak = readmatrix('data.csv');

Denbora_sec     = datuak(:, 1) * 0.020;
IragaziGabe     = datuak(:, 2);
Seinalea        = datuak(:, 3);
paladaKop       = datuak(:, 4);
GoiMuga         = datuak(:, 5);
BeheMuga        = datuak(:, 6);

diff_kont = [0; diff(paladaKop)];
gailurrak = find(diff_kont > 0);

% Seleccionar solo las primeras 5 paladas detectadas
NUM_PALADAS = 5;
if length(gailurrak) >= NUM_PALADAS
    gailurrak_5 = gailurrak(1:NUM_PALADAS);
else
    gailurrak_5 = gailurrak; % Por si hay menos de 5 en total
end

gailurX = Denbora_sec(gailurrak_5);
gailurY = Seinalea(gailurrak_5)/1000;

% Determinar el límite del tiempo (X) justo un poco después de la 5ª palada (+ 1 segundo de margen)
if ~isempty(gailurrak_5)
    limite_X_max = Denbora_sec(gailurrak_5(end)) + 1.0; 
else
    limite_X_max = 500 * 0.020; % Valor por defecto si no hay detecciones
end

% Grafikoa sortu
figure('Name', 'Paladen detekzioa eta mugak (Lehenengo 5ak)', 'NumberTitle', 'off');
hold on;

plot(Denbora_sec, Seinalea/1000, 'b-', 'LineWidth', 1.8);
plot(Denbora_sec, IragaziGabe/1000, ':', 'Color', [0.85, 0.45, 0.1], 'LineWidth', 1.2);
plot(Denbora_sec, GoiMuga/1000, 'g--', 'LineWidth', 1.2);
plot(Denbora_sec, BeheMuga/1000, 'm--', 'LineWidth', 1.2);

yline(0.2, 'k:', 'LineWidth', 1.2);

if ~isempty(gailurrak_5)
    plot(gailurX, gailurY, 'r^', 'MarkerFaceColor', 'r', 'MarkerSize', 8);
end

grid on;
xlabel('Denbora (s)');
ylabel('Azelerazioa (g)');

% Ajuste automático del eje X para recortar la vista tras la 5ª palada
xlim([min(Denbora_sec), limite_X_max]);

title(sprintf('Paladen detekzioa (Palada kopurua: %d)', length(gailurrak_5)));
legend('Seinalea', 'Iragazi gabeko seinalea', 'Goi Muga', 'Behe Muga', 'Indar Minimoa (0,2g)', 'Palada detektatuta', 'Location', 'northeast');
