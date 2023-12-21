import './style.css'
import { setupColorPicker, setupModeSelect } from "./init.ts";
import { DIV_PICKER_ID, MODE_RADIO_BUTTONS_ID } from './consts.ts';

document.querySelector<HTMLDivElement>('#app')!.innerHTML = `
  <div id="container">
    <h1 id="title">LED PANEL</h1>
    <div id="${DIV_PICKER_ID}"></div>
    <div id="modes">
         <input type="radio" class="${MODE_RADIO_BUTTONS_ID}" name="mode" value="0" checked>
         <label for="mode">None</label>
         <input type="radio" class="${MODE_RADIO_BUTTONS_ID}" name="mode" value="1">
         <label for="contactChoice1">Wave</label>
    </div>
  </div>
`
setupColorPicker();
setupModeSelect();