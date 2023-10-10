# Woonkamermodule - FAQ

Veelgevraagde informatie over de woonkamermodule.

# 1. Welke gegevens verzamelt dit apparaat?

Elke 10 minuten meet de woonkamermodule:

- de binnentemperatuur;
- de CO₂-concentratie;
- de luchtvochtigheid;
- het aantal bewoners[^1] dat aanwezig is.

[^1]: Het apparaatje telt alleen smartphones mee als ze zijn aangemeld zijn op dit apparaat om meegeteld te worden door dit apparaat; zie ook vraag 4.

## 2. Hoe kan ik het apparaatje installeren?

Zie hiervoor de [installatiehandleiding](../../installation/).

## 3. Hoe kan ik het apparaatje opnieuw koppelen aan wifi?

Een wifi-reset van het apparaatje kan nodig zijn als je wifinetwerk thuis verandert, als je het apparaatje aan een ander wifinetwerk thuis wilt koppelen of om andere redenen.

De wifi-reset werkt als volgt:

1. Hou de knop bovenop de module ingedrukt (je voelt een duidelijke klik).
2. Na 10 seconden gaat een groen lampje vlak bij het knopje 5 keer hebt zien knipperen (als het te licht is zie je het wellicht niet).
3. Laat de knop daarna los.
4. De Info? Scan! QR-code wordt vervangen door een QR-code zonder onderschrift.
5. Scan deze QR-code met de NeedForHeat app en volg de aanwijzingen.

## 4. Hoe kan ik mijn smartphone en die van mijn huisgenoten aanmelden voor het meetellen?

Voor het onderzoek is het nodig dat dit apparaatje de aanwezigheid van jou en je huisgenoten kan tellen. Dat doet dit apparaatje door af en toe het aantal aanwezige smartphones te tellen. Je moet hiervoor aan het begin van de meetperiode de smartphone van jezelf en die van elke huisgenoot éénmalig aanmelden op het apparaatje. Zo worden alleen huigenoten meegeteld (en niet buren). Om een smartphone aan te melden, ga je als volgt te werk:

1. Gebruik het zwarte wieltje met het knopje aan de zijkant (je komt dan in het `SMARTPHONES:`-scherm)
2. Blader met het zwarte wieltje één regel naar beneden `+ toevoegen`` en druk het wieltje in om het te selecteren.
3. Je ziet nu het `TOEVOEGEN?`-scherm met instructies wat je op de smartphone moet doen.
4. Ga verder op de smartphone (op een iPhone of Android smartphone).
    1. Zorg ervoor dat de smartphone is ingeschakeld en ontgrendeld.
    2. Ga naar `Instellingen` > `Bluetooth``.
    4. Zorg ervoor dat Bluetooth is ingeschakeld door de schakelaar aan te zetten.
    5. Je smartphone zal nu automatisch zoeken naar beschikbare apparaten. Wacht tot `NeedForHeat_OK` in de lijst verschijnt.
    6. Tik op `NeedForHeat_OK` om de koppeling te starten.
    
5. Een geslaagde koppeling bevestigt het meetapparaatje met een duidelijke piep; daarna wordt de naam van toegevoegde smartphone toegevoegd aan de lijst die op het schermpje van het meetapparaatje wordt gedoont.

Als het de eerste keer niet lukt, probeer het dan a.u.b. nog een keer.

Je kunt een menu op het scherm altijd verlaten door met het zwarte wieltje aan de zijkant te bladeren naar `terug` en dat te selecteren door het zwarte wieltje in te drukken.

Als je een verkeerde smartphone hebt toegevoegd of als je wilt dat deze niet langer wordt meegeteld, kun je deze verwijderen door naar de naam van de smartphone te bladeren, deze te selecteren (zwarte wieltje indrukken) en het verwijderen te bevestigen.

Als je 2 minuten het zwarte wieltje aan de zijkant niet gebruikt hebt, zal het meetapparaatje vanzelf terugkeren in de normale stand met de QR-code met onderschrift `Info? Scan!`

## 5. Bijft de smartphone verbonden met het apparaatje?

Nee, nadat een smartphone één keer gekoppeld is aan "NeedForHeat_OK" wordt de verbinding direct verbroken. Eenmaal gekoppelde apparaten worden automatisch meegeteld, zelfs zonder een actieve verbinding.

## 6. Moet Bluetooth de hele meetperiode op de toegevoegde smartphones aan blijven staan?

Ja. Verder hoef je niets te doen; detectie en meetellen van aanwezigheid gaat geheel automatisch. Veel mensen laten  Bluetooth tegenwoordig standaard aan staan; het heeft tegenwoordig nauwelijks nog invloed op de batterijduur van je smartphone.

## 7. Welke techniek gebruikt dit apparaatje om aanwezigheid te detecteren?

Dit apparaatje gebruikt [Bluetooth name requests om aanwezigheid van smartphones te detecteren](https://github.com/energietransitie/twomes-generic-esp-firmware/blob/main/src/presence_detection/README.md#general-info).


## 8. Waar kan ik meer technisch info vinden over dit apparaatje?

De broncode van dit meetapparaatje is openbaar beschibaar via GitHub via  [twomes-co2-occupancy-scd41-m5coreink-firmware](https://github.com/energietransitie/twomes-co2-occupancy-scd41-m5coreink-firmware).

## Wat als ik andere vragen of opmerkingen heb?
Stuur dan een e-mail naar de helpdesk van het NeedForHeat-onderzoek via [needforheatonderzoek@windesheim.nl](needforheatonderzoek@windesheim.nl).