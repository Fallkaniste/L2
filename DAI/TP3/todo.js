"use strict";  // le mode strict impose une version plus exigente de Javascript

// Demande le lancement de l'exécution quand toute la page Web sera chargée
window.addEventListener('load', go);

// SAM Design Pattern : http://sam.js.org/
let actions,
  model,
  state,
  view;

// Point d'entrée de l'application
function go() {
  console.log('GO !');

  // Initialise le modèle avec la liste de départements et un mode d'affichage
  model.init({
    items:  [{text: 'À faire hier'        , done:true },
            {text: 'À faire aujourd\'hui', done:false},
            {text: 'À faire demain'      , done:false}]
  });

  // Appelle l'affichage de l'application.
  state.samUpdate(model);
}

//------------------------------------------------------------------ Actions ---
// Actions appelées dans le code HTML quand des événements surviennent
//
actions = {
  doneItem(data) {
    model.samPresent({doneItem: data.index});
  },
  // Demande au modèle d'ajouter un item à son tableau de tâches à faire.
  // Lui envoit pour cela un objet avec une propriété 'inputField' qui
  // désigne l'id de l'élément qui contient le texte à ajouter.
  addItem(data) {
    let text = document.getElementById(data.inputField).value;
    if (text != '') {
      model.samPresent({
        newItem: text
      });
    }
  },

  removeDoneItems(data) {
  let activeItems = model.items.filter((v,i,a)=>{
    if (v.done == false) {
        return(v);
    }
  });
  model.samPresent({removedDoneItems: activeItems});
  }

};
//-------------------------------------------------------------------- Model ---
// Unique source de vérité de l'application
//
model = {
  items: [],
  done: false,
  isEditMode: false,

  init(data) {
    this.items = data.items || [];
  },

  // Demande au modèle de se mettre à jour en fonction des données qu'on
  // lui présente.
  // l'argument data est un objet confectionné dans les actions.
  // Les propriétés de data désignent la modification à faire sur le modèle.
  samPresent(data) {
    const has = Object.prototype.hasOwnProperty; // test si la propriété
    // d'un objet est présente

    // Si l'objet data possède la propriété 'newItem'
    // alors on ajoute ce nouvel item au tableau de tâches de model.
    if (has.call(data, 'newItem')) {
      var items = { text: data.newItem, done: false };
      this.items.push(items);

      console.log(this.items.length+' élément(s) : '+ this.items); // TODO: pourra être supprimé...
    }

     if (has.call(data, 'doneItem')) {
      let index = data.doneItem;
      this.items[index].done = !this.items[index].done;  // inversion du booléen !
      console.log(index+' : '+this.items[index].done);   // pour débug...
    }
    if (has.call(data, 'removedDoneItems')) {
      this.items = data.removedDoneItems;
    }
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
  //  if(model.items.filter(v => v.done == true)).length > 0){this.hasDoneItems = true};
    let test = model.items.filter(v => v.done == true);
    if (test.length > 0 ) {
      this.hasDoneItems = true;
    }else {
      this.hasDoneItems = false;
    }
    this.samRepresent(model);

    // this.samNap(model);
  },

  // Met à jour l'état de l'application, construit le code HTML correspondant,
  // et demande son affichage.
  samRepresent(model) {
    let representation = 'Oops, should not see this...';

    representation = view.normalInterface(model, this);

    // Appel l'affichage du HTML généré.
    view.samDisplay(representation);
  },

};
//--------------------------------------------------------------------- View ---
// Génération de portions en HTML et affichage
//
view = {

  // Injecte le HTML dans une balise de la page Web.
  samDisplay(representation) {
    const app = document.getElementById('app');
    app.innerHTML = representation;
  },

  // Renvoit le HTML
  normalInterface(model, state) {
    let li_items = this.listItems(model,state);
    let li_bouton = this.boutonsValue(state);
    let li_boutonEditText = this.boutonsEditValue(model);
    return `
     <style type="text/css">
	li.done {
  	text-decoration: line-through;
  	}
	</style>
      <h2> Todo List </h2>
      <input id="inputText" type="text" />
      <button onclick="actions.addItem( {e: event, inputField:'inputText'} )">Todo</button>
      <ul>
      	${li_items}
      </ul>
        ${li_bouton} <button>${li_boutonEditText}</button>
      `;
  },
  boutonsEditValue(state){
    if(model.isEditMode) {
      return('Edit Mode')
    }else {
      return('Todo Mode')
    }
  },
  boutonsValue(state){
    if (state.hasDoneItems) {
      return('<button onclick="actions.removeDoneItems()">Remove done items</button>')
    }else {
      return('<button disabled="disabled">Remove done items</button>')
    }
  },
  listItems(model, state) {
    console.log(model.items)
    let li_items = model.items.map((v,i,a)=>{
    	let raye = '';
    	if (v.done) {raye = 'class="done"';}
    	return('<li onclick="actions.doneItem({index:'+i+'})" '+raye+'>'+ v.text+'</li>');

    }).join('\n');
    return li_items;
  }

};
