# KalimaTuto

Documentations : etc/doc

- API_Kalima : Presentation rapide de Kalima
- JavaExample : Tuto pour se connecter et interagir avec la blockchain en Java
- AndroidExample : Tuto pour se connecter et interagir avec la blockchain via le service Kalima pour Android
- CSharpExample : Tuto pour se connecter et interagir avec la blockchain en C#
- nodeJSAPI : Appels REST vers Kalima
- Smart_Contracts : Création des Smart Contracts

Librairies : etc/lib

- Kalima.jar : API Kalima pour Java
- KalimaSC.jar : API Kalima incluant les éléments nécessaires pour exécuter des smarts contracts, pour Java
- kalima-android-lib-release.aar : Librairie du service Kalima pour Android
- dll/* : dll nécessaires pour créer un projet en C#

Exemple(s) de smart contract(s) : KalimaSmartContracts

- sensors.js : Smart Contract qui déclanche une alarme dans /fire à chaque fois la valeur ajoutée dans /sensors est supérieure à un seuil
- fire.js : Smart Contract permettant d'inverser le string ajouté dans /fire
- reverse_string.js : Smart Contract permettant d'inverser un string 