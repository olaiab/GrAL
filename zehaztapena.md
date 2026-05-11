### Palada kontagailua
Definitutako gailuaren ideia honetan dago oinarrituta:

https://www.vermontc2.com/tienda/speedcoach-gps/

Pantailan agertzen dena kontuan harturik, paladak/minutuko, denbora, 500mko denbora (split) eta distantzia markatzen du.

##### Sentsoreak:
- Azelerometroa: beharrezkoa, azelerazio pikoak kontuan harturik paladak/minutuko eta paladen kontagailua kalkulatzen ditu.
- GPS-a: abiadura neurtzeko; GPS-a edukiz ere entrenamenduen informazioa gorde daiteke gerora informazioa transferitzeko eta ikusteko.
- Termometroa (hautazkoa)

##### Gainerako piezak:
- Pantaila bat; askotan eguzkitan erabiltzen denez, tinta elektronikoa erabiltzen duten pantaila egokia izango litzateke.
- Bateria/pilak
- SD txartel bat entrenamenduak gorde ahal izateko.

##### Algoritmoak:
- Azelerometroan:
  - Seinalearen filtraketa
  - Paladen maiztasunarekin paladak/minutuko kalkulatu
  - Puntu gorenaren detekzioa: jasotako samplea muga baten gainetik badago palada bat da. (Nola kalkulatu muga??)
```
if (sample > muga) && (sample - 1 < muga) -> palada
```

- GPS: (posizioa (latitudea eta longitudea) emanda)
  - Abiadura: (bi posizioren arteko desberdintasuna)/(maiztasuna)
  - Split: zenbat denboratan egiten diren metro zehatz batzuk (500m normalean); metroak/abiadura

##### Pantailaren irteera (beharrezkoak):
1. Paladak minutuko (SPM)
2. Kronoa
3. Split
4. Egindako distantzia

##### Pantailaren irteera (hautazkoak):
1. Ordua
2. Tenperatura

##### Botoiak:
1. Pizteko/itzaltzeko botoia
2. Entrenamendua martxan jarri / gelditzeko botoia
3. Entrenamendua gordetzeko eta berri bat hasteko botoia
4. (Hautazkoa) Gauean entrenatu ezkero, pantailak argia izatea garrantzitsua da; iluminazioko botoia.

Adibidez:

```
SW1: Mantenduz, piztu / itzali
SW2: Sakatuz, entrenamendua martxan jarri / gelditu.
Geldirik egonda entrenamendu berria nahi bada (eta aurrekoa gorde) botoia mantendu --> "Entrenamendu berria Bai/Ez" --> "Aurreko entrenamendua gorde Bai/Ez"
SW3: Argia piztu/itzali
```

##### Datuak gordetzeko modua (SD txartela):
CSV moduan gorde, hurrengo datuekin: denbora, latitudea, longitudea, abiadura, paladak minutuko. Honela etorkizunean datuak tratatzeko aplikazio bat garatu daiteke mapa batean ibilbidea, abiadura eta dena delako datuak adieraziz. Entrenamendu berri bakoitzeko fitxategi berri bat.