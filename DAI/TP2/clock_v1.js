"use strict";

// Demande le lancement de l'exécution quand toute la page Web sera chargée
window.addEventListener('load', go);

// SAM Design Pattern : http://sam.js.org/
let actions, model, state, view;

// Point d'entrée de l'application
function go() {
  console.log('GO !');

  // Pour tester des choses pendant le développement...
  // à commenter quand pas besoin
  sandbox();

  // Appelle l'affichage de l'application.

  actions.updateTime(model);
  state.samUpdate(model);
}

// Bac à sable pour faire des tests
function sandbox() {

  // function actions_updateTime(data) {
  //   const date = new Date();
  //   const hh = date.getHours();
  //   const mm = date.getMinutes();
  //   const ss = date.getSeconds();
  //   const time = [hh,mm,ss];
  //   console.log(data.message + time.join(':') );
  // }
  //
  // function actions_fireAlarm(data) {
  //   console.log(data.message);
  //   window.clearInterval(intervalId);  // et arrête l'horloge !
  // }
  //
  // const intervalId = window.setInterval( ()=>{actions_updateTime({message: 'Il est : '})}, 1000);
  //
  // // Lance une alarme dans 7 secondes !
  // const seconds = 7;
  // const currentDate = new Date();
  // let   alarmDate   = new Date();
  // alarmDate.setSeconds(alarmDate.getSeconds() + seconds);
  // const delay = alarmDate - currentDate;   // durée en millisecondes
  // const timeoutId  = window.setTimeout ( ()=>{actions_fireAlarm ({message: 'Alarme déclenchée !'})}, delay);
}

//------------------------------------------------------------------ Actions ---
// Actions appelées dans le code HTML quand des événements surviennent
//
actions = {

  updateTime() {
    let date = new Date();
    let time = [date.getHours(),date.getMinutes(),date.getSeconds()];
    model.samPresent({updatedTime : time});
  },  // bouton "Heure courante" et setInterval()

  startTime() {
    console.log('appelle starttime ...');
    model.samPresent({startTime : true});
  },   // bouton "Démarrer"

  stopTime() {
    console.log('appelle stoptime ...');
    model.samPresent({stopTime : false});
  },    // button "Arrêter"

  addAlarm() {
    const date = new Date();
    const newAlarm = {
      time: [date.getHours(),date.getMinutes()+1,0],
      message: '',
      timeoutId: null,
    };
    model.samPresent({addAlarm : newAlarm});
  },    // button "Ajouter une alarme"

  changeAlarmHoursMinutes(data) {
    if (data.part == 'hour') {
      model.samPresent({changedHour : data.v , index : data.index});
    }else if (data.part == 'minutes') {
      model.samPresent({changedMinutes : data.v , index : data.index});
    }
  },  // sélection de l'heure et des minutes

  changeAlarmDescription(data) {
    model.samPresent({changedAlarmDescription : data.v , index : data.index});
  },   // saisie d'une description

  removeAlarm(data) {
    model.samPresent({removedAlarm : data.index});
  },   // button "Enlever cette alarme"

  setAlarm(data) {
    if (data.c) {
      let currentDate = new Date();
      let   alarmDate   = new Date();
      alarmDate.setHours((model.alarms.values[data.index].time[0]))
      alarmDate.setMinutes((model.alarms.values[data.index].time[1]))
      alarmDate.setSeconds((model.alarms.values[data.index].time[2]))
      const delay = alarmDate - currentDate;
      model.samPresent({setAlarm : delay , index : data.index});
    }else {
      model.samPresent({unsetAlarm : null , index : data.index});
    }

  },      // checkbox pour enclencher une alarme

  fireAlarm(data) {      // lancée par le setTimeout() de l'alarme
    alert("Alarme !\n\nil est "+data.alarms.time[0]+":"+data.alarms.time[1]+"\n\nmessage : "+data.alarms.message+"")
  },
};

//-------------------------------------------------------------------- Model ---
// Unique source de vérité de l'application
//
model = {
  time: {
    value: [],  // heures, minutes, secondes
    isOn: false,              // rafraichissement récurrent de l'heure
    intervalId: null,         // ref sur le timer récurrent
    sectionId: 'time',        // identifiant de la section HTML
    hasChanged: true,         // rafraichissement de la section nécessaire ou pas
  },
  alarms: {
    values: [                 //  tableau d'objets représentants des alarmes
      // {
      //   time: [],               // heures, minutes, secondes de l'alarme
      //   message: '',            // description de l'alarme
      //   timeoutId: null,        // ref sur le timer d'alarme
      // },
    ],
    sectionId: 'alarms',      // identifiant de la section HTML
    hasChanged: true,         // rafraichissement de la section nécessaire ou pas
  },

  // Demande au modèle de se mettre à jour en fonction des données qu'on
  // lui présente.
  // l'argument data est un objet confectionné dans les actions.
  // Les propriétés de data désignent la modification à faire sur le modèle.
  samPresent(data) {
    const has = Object.prototype.hasOwnProperty; // test si la propriété
    //                                              d'un objet est présente

    if (has.call(data, 'updatedTime')) {
      model.time.value = data.updatedTime;
    //  console.log(model.time.value);
      this.time.hasChanged = true;
    }
    if (has.call(data, 'startTime')) {
      model.time.intervalId = window.setInterval( ()=>{actions.updateTime()}, 1000);
      model.time.isOn = data.startTime;
      this.time.hasChanged = true;
    }
    if (has.call(data, 'stopTime')) {
      window.clearInterval(model.time.intervalId);
      model.time.isOn = data.stopTime;
      this.time.hasChanged = true;
    }
    if (has.call(data, 'addAlarm')) {
      model.alarms.values.push(data.addAlarm);
      this.alarms.hasChanged = true;
    }
    if (has.call(data, 'removedAlarm')) {
      clearTimeout(model.alarms.values[data.removedAlarm].timeoutId);
      model.alarms.values[data.removedAlarm].timeoutId = null;
      this.alarms.values.splice(data.removedAlarm,1);
      this.alarms.hasChanged = true;
    }
    if (has.call(data, 'changedHour')) {
      model.alarms.values[data.index].time[0] = data.changedHour;
      this.alarms.hasChanged = true;
    }
    if (has.call(data, 'changedMinutes')) {
      model.alarms.values[data.index].time[1] = data.changedMinutes;
      this.alarms.hasChanged = true;
    }
    if (has.call(data, 'changedAlarmDescription')) {
      model.alarms.values[data.index].message = data.changedAlarmDescription;
      this.alarms.hasChanged = true;
    }
    if (has.call(data, 'setAlarm')) {
      model.alarms.values[data.index].timeoutId = setTimeout( ()=>{actions.fireAlarm({alarms : model.alarms.values[data.index]})} , data.setAlarm);
      this.alarms.hasChanged = true;
    }
    if (has.call(data, 'unsetAlarm')) {
      clearTimeout(model.alarms.values[data.index].timeoutId);
      model.alarms.values[data.index].timeoutId = null;
      this.alarms.hasChanged = true;
    }
    // TODO: et les suivants...

    // Demande à l'état de l'application de prendre en compte la modification
    // du modèle
    state.samUpdate(this);
  }
};
//-------------------------------------------------------------------- State ---
// État de l'application avant affichage
//
state = {

  samUpdate(model) {

    this.samRepresent(model);
    // this.samNap(model);
  },

  // Met à jour l'état de l'application, construit le code HTML correspondant,
  // et demande son affichage.
  samRepresent(model) {
    let representation = 'Oops, should not see this...';

    if (model.time.hasChanged) {      // alors nouvelle représentation pour l'heure
      model.time.hasChanged = false;
      representation = view.timeUI(model, this);
      view.samDisplay(model.time.sectionId, representation);
    }
    if (model.alarms.hasChanged) {    // alors nouvelle représentation pour les alarmes
      model.alarms.hasChanged = false;
      representation = view.alarmsUI(model, this);
      view.samDisplay(model.alarms.sectionId, representation);
    }
  }
};
//--------------------------------------------------------------------- View ---
// Génération de portions en HTML et affichage
//
view = {

  // Injecte le HTML dans une balise de la page Web.
  samDisplay(sectionId, representation) {
    const section = document.getElementById(sectionId);
    section.innerHTML = representation;
  },

  // Renvoit le HTML pour l'affichage de l'heure
  timeUI(model, state) {
  //  console.log(model.time.value);

    let time = (''+(model.time.value).join(':'));
    let startstop = this.startstopvalue(model);
    return `
    <section>
      <time>${time}</time>
      <div>
        <button onclick="actions.updateTime()" class="time">Heure courante</button>
        <button ${startstop}</button>
      </div>
    </section>
    `;
  },

  // Renvoit le HTML pour la gestion des alarmes
  alarmsUI(model, state) {
    // console.log('alarmsUI ',model.alarms.values);
    let alarms = this.addAlarm(model,state);
    return `
    <section>
      <div class="alarmes">
        ${alarms}
      </div>
      <button onclick="actions.addAlarm()" class="ajouter">Ajouter une alarme</button>
    </section>
    `;
  },

  startstopvalue(model){
    //console.log(model.time.isOn);
    if(model.time.isOn) {
      return('onclick="actions.stopTime()" class="time">Arrêter')
    }else {
      return('onclick="actions.startTime()" class="time">Démarrer')
    }
  },

  addAlarm(model,state){
    var alarms=[],valuesH=[],valuesM=[],deb,select,text,checked,disable;
    if (model.alarms.values.length > 0) {
  for (let j = 0; j < model.alarms.values.length; j++) {

    for (let i = 0; i <= 23; i++) {
      if (i<10) {deb=0;}else{deb=''}
        if (i == model.alarms.values[j].time[0]) {select='selected="selected"';}else{select='';}
        valuesH[i]='<option '+select+' value="'+deb+i+'">'+deb+i+'</option>'
    }
    for (let i = 0; i <= 59; i++) {
      if (i<10) {deb=0;}else{deb='';}
      if (i == model.alarms.values[j].time[1]) {select='selected="selected"';}else{select='';}
      valuesM[i]='<option '+select+' value="'+deb+i+'">'+deb+i+'</option>'
    }

    if (model.alarms.values[j].timeoutId != null) {
      checked = 'checked="checked"';
      disable = 'disabled="disabled"';
    }else {
      checked = '';
      disable = '';
    }
      alarms[j]=`<div class="alarme">
        <input onclick="actions.setAlarm({c: checked , index : ${j}})" type="checkbox" ${checked}/>
        <select onchange="actions.changeAlarmHoursMinutes({v: value, part:'hour', index:${j}})" ${disable}>
          ${valuesH}
        </select>
        <select onchange="actions.changeAlarmHoursMinutes({v: value, part:'minutes', index:${j}})" ${disable}>
          ${valuesM}
        </select>
        <input onchange="actions.changeAlarmDescription({v: value, index:${j}})" type="text" placeholder="Description de l'alarme" value="${model.alarms.values[j].message}" ${disable}/>
        <button onclick="actions.removeAlarm({index:${j}})" class="enlever">Enlever cette alarme</button>
      </div>`
    }
  }else {
    alarms =["",""];
  }
    return(alarms.join('\n'));
  },

};
