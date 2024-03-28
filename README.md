# BudgetManager

## Description
BudgetManager est une application de gestion de budget développée avec C++ et le framework Qt. Elle permet aux utilisateurs d'enregistrer leur budget, d'ajouter des dépenses, de visualiser l'évolution de leur portefeuille financier, et d'obtenir un aperçu visuel des catégories de dépenses via un diagramme circulaire. Les utilisateurs peuvent également sauvegarder les informations de leur portefeuille sous forme d'image ou de fichier texte pour une gestion et un suivi facilités.

![2024-03-28-13-28-43](https://github.com/nexiath/BudgetManager/assets/108474515/eb736eff-6127-4814-865e-fa77a9d5b46d)

## Prérequis
Pour compiler et exécuter BudgetManager, les composants suivants doivent être installés sur votre système :

### Qt 6.6
BudgetManager utilise Qt 6.6 pour son interface utilisateur et ses fonctionnalités. Suivez ces étapes pour installer Qt 6.6 :

1. **Téléchargement de l'installateur :**
   - Visitez [le site officiel de Qt](https://www.qt.io/download) et téléchargez le Qt Online Installer adapté à votre système d'exploitation.
   
2. **Installation de Qt :**
   - Exécutez le programme d'installation téléchargé. Si nécessaire, acceptez les conditions d'utilisation et connectez-vous avec votre compte Qt. Si vous n'en avez pas, vous aurez l'option d'en créer un gratuitement.
   - Une fois connecté, vous serez dirigé vers le sélecteur de composants. Ici, développez la section correspondant à Qt 6.6 et sélectionnez les composants requis pour votre développement, comme le kit de développement (SDK) pour votre système d'exploitation et le compilateur spécifique (par exemple, MinGW 64-bit ou MSVC2019 64-bit pour Windows).
   - **Important :** N'oubliez pas de cocher également 'Sources', cela pourrait être utile pour le débogage ou si vous avez besoin de consulter le code source de Qt pour quelque raison que ce soit.

3. **Finalisation de l'installation :**
   - Suivez les instructions à l'écran pour terminer l'installation. Cela peut prendre un certain temps en fonction de votre connexion Internet et des composants sélectionnés.

### Qt Charts
Pour générer des visualisations graphiques, BudgetManager utilise Qt Charts, qui doit être installé séparément :

1. **Installation pendant le processus de Qt :**
   - Si vous installez Qt pour la première fois, assurez-vous de sélectionner 'Qt Charts' sous la section 'Additional Libraries' lors de l'étape du sélecteur de composants.
   
2. **Ajout de Qt Charts à une installation existante :**
   - Si Qt est déjà installé sans Qt Charts, vous pouvez ajouter cette bibliothèque en ouvrant le Qt Maintenance Tool, qui se trouve dans le dossier d'installation de Qt. Sélectionnez 'Add or Remove Components' (Ajouter ou supprimer des composants), puis naviguez jusqu'à trouver 'Qt Charts' sous la version appropriée de Qt. Cochez la case correspondante et suivez les instructions pour l'installer.

### Compiler et exécuter BudgetManager
Avec Qt 6.6 et Qt Charts installés, vous êtes prêt à compiler BudgetManager :

- **Utilisation de Qt Creator :**
  - Lancez Qt Creator et ouvrez le projet BudgetManager en sélectionnant le fichier `.pro`.
  - Avant de compiler, assurez-vous que le kit de développement sélectionné correspond à la version de Qt que vous avez installée (par exemple, Qt 6.6 MinGW 64-bit).
  - Cliquez sur 'Build' (Compiler) pour compiler le projet, puis sur 'Run' (Exécuter) pour démarrer l'application.

- **Compilation en ligne de commande :**
  - Vous pouvez également compiler et exécuter le projet en utilisant la ligne de commande. Ouvrez un terminal ou une invite de commandes, naviguez jusqu'au répertoire du projet, et utilisez les commandes `qmake` suivies de `make` (sous Linux/Mac) ou `mingw32-make` (sous Windows avec MinGW) pour compiler le projet. Ensuite, exécutez l'exécutable généré pour démarrer BudgetManager.

## Fonctionnalités
- **Enregistrement du budget :** Commencez par définir votre budget pour suivre vos finances.
- **Ajout de dépenses :** Saisissez vos dépenses en les catégorisant pour mieux comprendre vos habitudes de consommation.
- **Visualisation de l'évolution :** Observez comment votre solde change au fil du temps.
- **Aperçu des dépenses :** Utilisez le diagramme circulaire pour une représentation visuelle des catégories de vos dépenses.
- **Sauvegarde et exportation :** Enregistrez votre portefeuille et vos dépenses en image ou en texte pour une consultation ultérieure.

## Utilisation
Après avoir lancé BudgetManager, suivez ces étapes pour gérer votre budget :

1. **Définir un budget :** Commencez par entrer votre budget total.
2. **Ajouter des dépenses :** Cliquez sur 'Ajouter une dépense' pour enregistrer chaque dépense en précisant la catégorie.
3. **Visualiser :** Consultez l'évolution de votre portefeuille et examinez le piechart pour comprendre la répartition de vos dépenses.
4. **Sauvegarder :** Exportez vos données en image ou en fichier texte via les options de sauvegarde.

---
BudgetManager - Gérez votre budget intelligemment.
