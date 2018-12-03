"use strict";

// Demande le lancement de l'exécution quand toute la page Web sera chargée
window.addEventListener('load', go);

// SAM Design Pattern : http://sam.js.org/
let actions, model, state, view;

//-------------------------------------------------------------------- Init ---
// Point d'entrée de l'application
function go() {
  console.log('GO !');

  sandbox();

  const data = {
    authors: 'Prénom1 NOM1 et Prénom2 NOM2',
    languagesSrc: ['fr', 'en', 'es'],
    languagesDst: ['fr', 'en', 'es', 'it', 'ar', 'eo', 'ja', 'zh'],
    langSrc: 'fr',
    langDst: 'en',
    translations : translations1,
  };

  actions.initAndGo(data);
  actions.tabsUpdate();

}

//-------------------------------------------------------------------- Tests ---

function sandbox() {
  function action_display(data) {
    // console.log(data);
    if (!data.error) {
      const language = languages[data.languageDst].toLowerCase();
      console.log(`'${data.expression}' s'écrit '${data.translatedExpr}' en ${language}`);
    } else {
      console.log('Service de traduction indisponible...');
    }
  }

  const expr = 'asperge';
  const langSrc = 'fr';
  const langDst = 'en';
  googleTranslation(expr, langSrc, langDst, action_display );
}

//------------------------------------------------------------------ Données ---

// Correspondance entre codes de langue et leur nom
// Pour d'autres langues, voir ici :  https://fr.wikipedia.org/wiki/Liste_des_codes_ISO_639-1
const languages = {
  fr: 'Français',
  en: 'Anglais',
  es: 'Espagnol',
  it: 'Italien',
  ar: 'Arabe',
  eo: 'Espéranto',
  ja: 'Japonais',
  zh: 'Chinois',
};

//------------------------------------------------------------------ Actions ---
// Actions appelées dans le code HTML quand des événements surviennent
//
actions = {

  initAndGo(data) {
    model.samPresent({
      do:'init',
      authors: data.authors,
      langSrc: data.langSrc,
      langDst: data.langDst,
      languagesSrc: data.languagesSrc,
      languagesDst: data.languagesDst,
      translations: data.translations,
    });
  },

  tabsUpdate() {
  let values = [], tab = [];
  for (let i = 0; i < model.translations.values.length; i++) {
    model.translations.values[i].forEach( (v,j,a)=>{
      if ((j%2 == 0)) {
        if((!tab.includes(v))) {
          tab.push(v);
          values.push({language : languages[v],occ : 1})
        }else {
          for (let k = 0; k < values.length; k++) {
            if (values[k].language == languages[v]) {
              values[k].occ ++;
            }
          }
        }
      }
    });
  }
    model.samPresent({
      do:'makeTabs',
      values : values,
      tabsIn : values.slice(0,3),
      tabsInSelect : values.slice(3,values.length)
      });
    },
  // TODO: Ajouter les autres actions...
};

//-------------------------------------------------------------------- Model ---
// Unique source de vérité de l'application
//
model = {
  tabs: {
    values :[],
    tabsIn: [],
    tabsInSelect: [],

  },
  request: {
    languagesSrc: [],
    languagesDst: [],
    langSrc: '',
    langDst: '',
    expression: '',
  },
  translations: {
    values:[
      // ['fr','Asperge','en','Asparagus'],
    ],
  },
  sorted: {
    // TODO: propriétés pour trier les colonnes
  },
  marked: {
    // TODO: propriétés pour les lignes marquées pour suppression
  },
  pagination: {
    // TODO: propriétés pour gérer la pagination
  },
  app: {
    authors: '',
    mode: 'main',    // in ['main', 'lang']
    sectionId: 'app',
  },

  // Demande au modèle de se mettre à jour en fonction des données qu'on
  // lui présente.
  // l'argument data est un objet confectionné dans les actions.
  // Les propriétés de data comportent les modifications à faire sur le modèle.
  samPresent(data) {

    switch (data.do) {

      case 'init':
        this.app.authors = data.authors;
        this.request.languagesSrc = data.languagesSrc;
        this.request.languagesDst = data.languagesDst;
        this.request.langSrc = data.langSrc;
        this.request.langDst = data.langDst;
        this.translations.values = data.translations;
        break;


      case 'makeTabs':
        this.tabs.values = data.values;
        this.tabs.tabsIn = data.tabsIn;
        this.tabs.tabsInSelect = data.tabsInSelect;
        break;

      default:
        console.error(`model.samPresent(), unknown do: '${data.do}' `);
    }

    // Demande à l'état de l'application de prendre en compte la modification
    // du modèle
    state.samUpdate(this);
  },

};
//-------------------------------------------------------------------- State ---
// État de l'application avant affichage
//
state = {
  tabs: {
    values : model.tabs.values,
    tabsIn : model.tabs.tabsIn,
    tabsInSelect : model.tabs.tabsInSelect
  },
  translations: {
    // TODO: données de traductions déduites de model (par langue notamment)
  },

  samUpdate(model) {

    this.samRepresent(model);
  },

  // Met à jour l'état de l'application, construit le code HTML correspondant,
  // et demande son affichage.
  samRepresent(model) {

    let representation = '';

    let headerUI = view.headerUI(model,state);
    let tabsUI = view.tabsUI(model,state);
    let requestUI = view.requestUI(model,state);
    let translationsUI = view.translationsUI(model,state);

    representation += headerUI + tabsUI + requestUI + translationsUI;

    // TODO: la représentation de l'interface est différente selon
    //       qu'on affiche l'onglet 'Traductions' (avec formulaire de traduction)
    //       ou qu'on affiche les onglets par langue...

    representation = view.generateUI(model, this, representation);

    view.samDisplay(model.app.sectionId, representation);
  },
};
//--------------------------------------------------------------------- View ---
// Génération de portions en HTML et affichage
//
view = {

  // Injecte le HTML dans une balise de la page Web.
  samDisplay(eltId, representation) {
    const elt = document.getElementById(eltId);
    elt.innerHTML = representation;
  },

  // Renvoit le HTML
  generateUI(model, state, representation) {
    return `
    <div class="container">
      ${representation}
    </div>
    `;
  },

  headerUI(model,state) {
    return `
    <section id="header" class="mt-4">
      <div class="row mb-4">
        <div class="col-6">
          <h1>Traducteur</h1>
        </div>
        <div class="col-6 text-right align-middle">
          <div class="btn-group mt-2">
            <button class="btn btn-primary">Charger</button>
            <button class="btn btn-ternary">Enregistrer</button>
            <button class="btn btn-secondary">Préférences</button>
            <button onclick="actions.makeTabs()" class="btn btn-primary">À propos</button>
          </div>
        </div>
      </div>
    </section>
    `;
  },

  tabsUI(model,state) {
    let tabsIn=[],tabsInSelect=[];
    for (let i = 0 ; i < model.tabs.tabsIn.length ; i++) {
      tabsIn[i]=`<li class="nav-item">
        <a class="nav-link " href="#">${model.tabs.tabsIn[i].language}
          <span class="badge badge-primary">${model.tabs.tabsIn[i].occ}</span>
        </a>
      </li>`
    }

    for (var i = 0; i < model.tabs.tabsInSelect.length; i++) {
      tabsInSelect[i] = `<option value="es">${model.tabs.tabsInSelect[i].language} (${model.tabs.tabsInSelect[i].occ})</option>`;
    }



    return `
    <section id="tabs">
      <div class="row justify-content-start ml-1 mr-1">
        <ul class="nav nav-tabs">
          <li class="nav-item">
            <a class="nav-link active"
              href="#">Traductions
              <span class="badge badge-primary">${model.translations.values.length}</span>
            </a>
          </li>
          ${tabsIn.join('\n')}
          <li class="nav-item">
            <select class="custom-select" id="selectFrom">
              <option selected="selected" value="0">Autre langue...</option>
              ${tabsInSelect}
            </select>
          </li>
        </ul>
      </div>
    </section>
    <br />
    `
  },

  requestUI(model,state) {
    return`
    <section id="request">
      <form action="">
        <div class="form-group">
          <fieldset class="form-group">
            <div class="row align-items-end">
              <div class="col-sm-3 col-5">
                <div class="form-group">
                  <label for="selectFrom">Depuis</label>
                  <select class="custom-select" id="selectFrom">
                    <option selected="selected" value="fr">Français</option>
                    <option value="en">Anglais</option>
                    <option value="es">Espagnol</option>
                  </select>
                </div>
              </div>
              <div class="form-group col-sm-1 col-2">
                <button class="btn btn-secondary" type="button">⇄</button>
              </div>
              <div class="col-sm-3 col-5">
                <div class="form-group">
                  <label for="selectTo">Vers</label>
                  <select class="custom-select" id="selectTo">
                    <option value="fr">Français</option>
                    <option selected="selected" value="en">Anglais</option>
                    <option value="es">Espagnol</option>
                    <option value="it">Italien</option>
                    <option value="ar">Arabe</option>
                    <option value="eo">Espéranto</option>
                    <option value="ja">Japonais</option>
                    <option value="zh">Chinois</option>
                  </select>
                </div>
              </div>
              <div class="col-sm-5 col-12">
                <div class="input-group mb-3">
                  <input value="" id="expressionText" type="text" class="form-control" placeholder="Expression..." />
                  <div class="input-group-append">
                    <button class="btn btn-primary" type="button">Traduire</button>
                  </div>
                </div>
              </div>
            </div>
          </fieldset>
        </div>
      </form>
    </section>
    `
  },

  transGeneration(model,state){
    let translations=[],text1,text2;
    for (let i = 0; i < model.translations.values.length; i++) {
      if (model.translations.values[i][0] == 'ar') {
        text1 = 'class="text-right"'
      }else {
        text1 = 'class="text-left"'
      }

      if (model.translations.values[i][2] == 'ar') {
        text2 = 'class="text-right"'
      }else {
        text2 = 'class="text-left"'
      }
      translations[i] = `<tr>
        <td class="text-center text-secondary"> ${i} </td>
        <td class="text-center">
          <span class="badge badge-info">${model.translations.values[i][0]}</span>
        </td>
        <td ${text1}>${model.translations.values[i][1].toLowerCase()}</td>
        <td class="text-center">
          <span class="badge badge-info">${model.translations.values[i][2]}</span>
        </td>
        <td ${text2}>${model.translations.values[i][3].toLowerCase()}</td>
        <td class="text-center">
          <div class="form-check">
            <input type="checkbox" class="form-check-input" />
          </div>
        </td>
      </tr>`
    }

    return(translations.join('\n'))
  },

  translationsUI(model,state) {
    let translations = view.transGeneration(model,state);
    return`
    <section id="translations">
      <fieldset>
        <legend class="col-form-label">Traductions</legend>
        <div class="table-responsive">
          <table class="col-12 table table-sm table-bordered">
            <thead>
              <th class="align-middle text-center col-1">
                <a href="#">N°</a>
              </th>
              <th class="align-middle text-center col-1">
                <a href="#">Depuis</a>
              </th>
              <th class="align-middle text-center ">
                <a href="#">Expression</a>
              </th>
              <th class="align-middle text-center col-1">
                <a href="#">Vers</a>
              </th>
              <th class="align-middle text-center ">
                <a href="#">Traduction</a>
              </th>
              <th class="align-middle text-center col-1">
                <div class="btn-group">
                  <button class="btn btn-ternary">Suppr.</button>
                </div>
              </th>
            </thead>
              ${translations}
            <tr>
              <td colspan="5" class="align-middle text-center"> </td>
              <td class="align-middle text-center">
                <div class="btn-group">
                  <button class="btn btn-secondary">Suppr. tous</button>
                </div>
              </td>
            </tr>

            </table>
          </div>

        </fieldset>
      </section>
    `
  },




};
