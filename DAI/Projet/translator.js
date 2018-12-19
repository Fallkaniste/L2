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
    langSrc: 'en',
    langDst: 'fr',
    translations : translations1,
  };

  actions.initAndGo(data);
  actions.tabsUpdate(model);

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
  const langSrc = 'en';
  const langDst = 'fr';
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
      tradPerP : 3,
      currPage : 0,
    });
  },

  tabsUpdate(data) {
  let values = [], tab = [];
  for (let i = 0; i < data.translations.values.length; i++) {
    data.translations.values[i].forEach( (v,j,a)=>{
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
  values.sort((a,b)=>b.occ-a.occ);
  console.table(values);
    data.samPresent({
      do:'makeTabs',
      values : values,
      tabsIn : values.slice(0,3),
      tabsInSelect : values.slice(3,values.length)
      });
    },

    changelangDst(data){
      model.samPresent({
        do : 'changelangDst',
        changedlangDst : data.value
      });
    },

    changelangSrc(data){
      model.samPresent({
        do : 'changelangSrc',
        changedlangSrc : data.value
      });
    },

    switchLang(){
      if ((model.request.languagesDst.indexOf(model.request.langSrc) != -1) & (model.request.languagesSrc.indexOf(model.request.langDst) != -1)) {
        model.samPresent({
          do:'switchLang',
          switchedLangSrc : model.request.langDst,
          switchedLangDst : model.request.langSrc
          });
      }else {
        console.log("switch impossible !");
      }

    },

    addTranslation(data){
      if (!data.error) {
        const language = languages[data.languageDst].toLowerCase();
        model.samPresent({
          do: 'addTranslation',
          newTranslation : [data.languageSrc,data.expression,data.languageDst,data.translatedExpr]
        });
      } else {
        console.log('Service de traduction indisponible...');
      }
      actions.tabsUpdate(model);
      actions.pagesUpdate();
    },

    translate(){
      googleTranslation(model.request.expression, model.request.langSrc, model.request.langDst, actions.addTranslation );
    },

    changeTransDescription(data){
      model.samPresent({
        do: 'changeTransDescription',
        newDescription : data.value
      });
    },

    markLine(data){
      console.log(data.checked);
      if (data.checked) {
        console.log(data.index);
        model.samPresent({
          do:'addMark',
          indexToAdd : data.index
        });

      }else {
        console.log(data.index);
        model.samPresent({
          do:'rmvMark',
          indexToRmv : data.index
        });
    }
    },

    removeTranslation(){
      model.samPresent({
        do:'removeTranslation',
        newTranslations : model.marked.indexs
      })
      actions.tabsUpdate(model);
      actions.pagesUpdate();
      actions.tabClicked({index : model.selectedTab});
    },

    removeAllTrad(){
      let res = confirm("Tout supprimer ?");
      if (res) {
        model.samPresent({
          do:'removeAllTrad',
          emptyTrad : []
        });
      }
      actions.tabsUpdate(model);
      action.pagesUpdate();
    },

    pagesUpdate(){
      model.samPresent({
          do:'pagesUpdate',
          numOfPages : Math.trunc(model.translations.values.length/model.pagination.tradPerP)+1,
      });
    },

    changeNumPerP(data){
      model.samPresent({
        do : 'changeNumPerP',
        newNumPerP : data.value
      });
    },

    changePage(data){
      model.samPresent({
        do : 'changePage',
        newCurrPage : data.value,
      });
    },

    nextPage(data){
      model.samPresent({
        do :'changePage',
        newCurrPage : data.value+1,
      });
    },

    prevPage(data){

      model.samPresent({
        do :'changePage',
        newCurrPage : data.value-1,
      });
    },

    tabClicked(data){
      model.selectedTab = data.index;
      state.selectedTab = data.index;
      let lang = model.tabs.values[data.index].language;
      console.log(model.tabs.values[data.index].language);
      let values =[];
      model.translations.values.forEach((v,i,a)=>{
        if (languages[v[0]] == lang | languages[v[2]] == lang) {
          return values.push(v);
        }
      });
      console.log(values);
      state.samPresent({

        do : 'tabClicked',
        isOn : true,
        values : values,
      });
      actions.tabsUpdate(state);
    },

    FirstTabClick(){
      state.samPresent({
        do : 'FirstTabClicked',
        isOn : false,
      });
    },
  // TODO: Ajouter les autres actions...
};

//-------------------------------------------------------------------- Model ---
// Unique source de vérité de l'application
//
model = {
  tabs: {
    selectedTab : "",
    values :[],
    tabsIn: [],
    tabsInSelect: []

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
    indexs : [],
  },
  pagination: {
    currPage: '',
    tradPerP: '',
    numOfPages: ''
    // TODO: propriétés pour gérer la pagination
  },
  app: {
    authors: '',
    mode: 'main',    // in ['main', 'lang']
    sectionId: 'app'
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
        this.pagination.tradPerP = data.tradPerP;
        this.pagination.numOfPages = Math.trunc(model.translations.values.length/model.pagination.tradPerP)+1;
        this.pagination.currPage = data.currPage
        break;

      case 'pagesUpdate':
        this.pagination.numOfPages = data.numOfPages;
        break;

      case 'makeTabs':
        this.tabs.values = data.values;
        this.tabs.tabsIn = data.tabsIn;
        this.tabs.tabsInSelect = data.tabsInSelect;
        break;

      case 'changelangDst':
        this.request.langDst = data.changedlangDst;
        break;

      case 'changelangSrc':
        this.request.langSrc = data.changedlangSrc;
        break;

      case 'switchLang':
        this.request.langDst = data.switchedLangDst;
        this.request.langSrc = data.switchedLangSrc;
        break;

      case 'changeTransDescription':
        this.request.expression = data.newDescription;
        console.log(this.request.expression);
        break;

      case 'addTranslation':
        this.translations.values.push(data.newTranslation);
        break;

      case 'addMark':
        this.marked.indexs.push(data.indexToAdd);
        this.marked.indexs.sort();
        console.log(this.marked.indexs);
        break;

      case 'rmvMark':
        this.marked.indexs.splice(this.marked.indexs.indexOf(data.indexToRmv),1);
        console.log(this.marked.indexs);
        break;

      case 'removeTranslation':
        model.marked.indexs.forEach((v,i,a)=> {
          if (data.newTranslations.lenght == 1) {
            model.translations.values.splice(model.marked.indexs[i],1)
          }else {
            model.translations.values.splice(model.marked.indexs[i]-(i),1)
          }

        });
        model.marked.indexs = [];
        break;

      case 'removeAllTrad':
        this.translations.values = data.emptyTrad;
        break;

      case 'changeNumPerP':
        this.pagination.tradPerP = data.newNumPerP;
        this.pagination.numOfPages = Math.trunc(model.translations.values.length/model.pagination.tradPerP)+1;
        console.log(this.pagination.tradPerP);
        console.log(this.pagination.numOfPages);
        break;

      case 'changePage':
        this.pagination.currPage = data.newCurrPage;
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
    selectedTab : "",
    values : [],
    tabsIn : [],
    tabsInSelect :[]
  },
  translations: {
    isOn : false,
    values : [],
  },
    samPresent(data) {
      switch (data.do) {
        case 'makeTabs':
          this.tabs.values = data.values;
          this.tabs.tabsIn = data.tabsIn;
          this.tabs.tabsInSelect = data.tabsInSelect;
          break;

        case 'tabClicked':
          state.translations.isOn = data.isOn;
          state.translations.values = data.values;

          break;

        case 'FirstTabClicked':
          state.translations.isOn = data.isOn;
          break;

      }
      state.samUpdate(model);
    },

  samUpdate(model) {

    this.samRepresent(model);
  },

  // Met à jour l'état de l'application, construit le code HTML correspondant,
  // et demande son affichage.
  samRepresent(model) {

    let representation = '';
    let tabsUI,translationsUI,requestUI = "";

    let headerUI = view.headerUI(model,state);


    if (state.translations.isOn) {
        tabsUI = view.tabsUI(state);
        translationsUI = view.translationsUI(state);
    }else {
        requestUI = view.requestUI(model,state);
        tabsUI = view.tabsUI(model);
        translationsUI = view.translationsUI(model);
    }

    console.log(state.translations.isOn);
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
            <button class="btn btn-primary">À propos</button>
          </div>
        </div>
      </div>
    </section>
    `;
  },

  tabsUI(data) {
    let tabsIn=[],tabsInSelect=[];
    for (let i = 0 ; i < model.tabs.tabsIn.length ; i++) {
      tabsIn[i]=`<li class="nav-item">
        <a onclick="actions.tabClicked({index : ${i}})" class="nav-link " href="#">${model.tabs.tabsIn[i].language}
          <span class="badge badge-primary">${model.tabs.tabsIn[i].occ}</span>
        </a>
      </li>`
    }

    for (var i = 0; i < data.tabs.tabsInSelect.length; i++) {
      tabsInSelect[i] = `<option value="es">${model.tabs.tabsInSelect[i].language} (${model.tabs.tabsInSelect[i].occ})</option>`;
    }



    return `
    <section id="tabs">
      <div class="row justify-content-start ml-1 mr-1">
        <ul class="nav nav-tabs">
          <li class="nav-item">
            <a onclick="actions.FirstTabClick()" class="nav-link active"
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
    let selected,langVers,langDepuis;
    langVers = model.request.languagesDst.map((v,i,a)=>{
      if(v==model.request.langDst){
        selected='selected="selected"'
      }else{
            selected=''
          };
            return `<option ${selected} value="${v}">${languages[v]}</option>`
          });

    langDepuis = model.request.languagesSrc.map((v,i,a)=>{
      if(v==model.request.langSrc){
        selected='selected="selected"'
      }else{
        selected=''
      }
      ;return `<option ${selected} value="${v}">${languages[v]}</option>`
      });

    return`
    <section id="request">
      <form action="">
        <div class="form-group">
          <fieldset class="form-group">
            <div class="row align-items-end">
              <div class="col-sm-3 col-5">
                <div class="form-group">
                  <label for="selectFrom">Depuis</label>
                  <select onchange="actions.changelangSrc({value : value})" class="custom-select" id="selectFrom">
                    ${langDepuis}
                  </select>
                </div>
              </div>
              <div class="form-group col-sm-1 col-2">
                <button onclick="actions.switchLang()" class="btn btn-secondary" type="button">⇄</button>
              </div>
              <div class="col-sm-3 col-5">
                <div class="form-group">
                  <label for="selectTo">Vers</label>
                  <select onchange="actions.changelangDst({value : value})" class="custom-select" id="selectTo">
                    ${langVers.join('\n')}
                  </select>
                </div>
              </div>
              <div class="col-sm-5 col-12">
                <div class="input-group mb-3">
                  <input value="${model.request.expression}" id="expressionText" type="text" class="form-control" onchange="actions.changeTransDescription({value: value})" placeholder="Expression..." />
                  <div class="input-group-append">
                    <button onclick="actions.translate()" class="btn btn-primary" type="button">Traduire</button>
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

  transGeneration(data){
    let translations=[],text1,text2,checked,finalTranslations=[];
    for (let i = 0; i < data.translations.values.length; i++) {
      if (data.translations.values[i][0] == 'ar') {
        text1 = 'class="text-right"'
      }else {
        text1 = 'class="text-left"'
      }

      if (model.translations.values[i][2] == 'ar') {
        text2 = 'class="text-right"'
      }else {
        text2 = 'class="text-left"'
      }
      if (model.marked.indexs.includes(i)) {
        checked = 'checked="checked"';
      }else {
        checked = '';
      }

      translations[i] = `<tr>
        <td class="text-center text-secondary"> ${i} </td>
        <td class="text-center">
          <span class="badge badge-info">${data.translations.values[i][0]}</span>
        </td>
        <td ${text1}>${data.translations.values[i][1].toLowerCase()}</td>
        <td class="text-center">
          <span class="badge badge-info">${data.translations.values[i][2]}</span>
        </td>
        <td ${text2}>${data.translations.values[i][3].toLowerCase()}</td>
        <td class="text-center">
          <div class="form-check">
            <input onclick="actions.markLine({index : ${i}, checked : checked})" type="checkbox" class="form-check-input" ${checked}/>
          </div>
        </td>
      </tr>`
    }


    if (translations.length > model.pagination.tradPerP) {
      for (let i = 0; i < Math.trunc(translations.length/model.pagination.tradPerP); i++) {
        for (let k = 0; k < model.pagination.tradPerP; k++) {
          finalTranslations.push(translations.splice(i,i+model.pagination.tradPerP));
        }
      }
    }else {
      finalTranslations = [translations];
    }


    return(finalTranslations);
  },

  translationsUI(data) {
    let pageSelect,pageNum = [],pageNumber=[];
    let translations = view.transGeneration(data);
    for (let i = 0; i < 3; i++) {
      if ((i+1)*3 == model.pagination.tradPerP) {
        pageSelect = 'selected="selected"';
      }else {
        pageSelect = '';
      }
      pageNum[i] = `<option ${pageSelect} value="${(i+1)*3}">${(i+1)*3}</option>`;
    }
    console.log(model.pagination.numOfPages);
    for (var i = 0; i < model.pagination.numOfPages; i++) {
      pageNumber[i]= `<li class="page-item active">
        <a onclick="actions.changePage({value : ${i}})" class="page-link" >${i+1}</a>
      </li>`
    }
    console.log(model.pagination.currPage);

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
                  <button onclick="actions.removeTranslation()" class="btn btn-ternary">Suppr.</button>
                </div>
              </th>
            </thead>
              ${translations[model.pagination.currPage].join('\n')}
            <tr>
              <td colspan="5" class="align-middle text-center"> </td>
              <td class="align-middle text-center">
                <div class="btn-group">
                  <button onclick="actions.removeAllTrad()" class="btn btn-secondary">Suppr. tous</button>
                </div>
              </td>
            </tr>

            </table>
          </div>


          <section id="pagination">
            <div class="row justify-content-center">

              <nav class="col-auto">
                <ul class="pagination">
                  <li class="page-item disabled">
                    <a onclick="actions.prevPage({value : ${model.pagination.currPage}})" class="page-link" tabindex="-1">Précédent</a>
                  </li>
                  ${pageNumber}
                  <li class="page-item disabled">
                    <a onclick="actions.nextPage({value : ${model.pagination.currPage}})" class="page-link" href="#">Suivant</a>
                  </li>
                </ul>
              </nav>

              <div class="col-auto">
                <div class="input-group mb-3">
                  <select onchange="actions.changeNumPerP({value : value})" class="custom-select" id="selectTo">
                    ${pageNum}
                  </select>
                  <div class="input-group-append">
                    <span class="input-group-text">par page</span>
                  </div>
                </div>
              </div>

            </div>
          </section>

        </fieldset>
      </section>
    `
  },




};
