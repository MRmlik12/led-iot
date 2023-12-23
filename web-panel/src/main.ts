import './style.css'
import { setupBrightnessRange, setupColorPicker, setupModeSelect } from "./init.ts";
import { BRIGHTNESS_RANGE_ID, DIV_PICKER_ID, MODE_RADIO_BUTTONS_ID } from './consts.ts';

document.querySelector<HTMLDivElement>('#app')!.innerHTML = `
  <div id="container">
    <h1 id="title">LED PANEL</h1>
    <div id="${DIV_PICKER_ID}"></div>
    <div id="slider">
        <label for="brightness" style="margin-right: 0.40rem">Brightness</label>
        <input id="${BRIGHTNESS_RANGE_ID}" type="range" name="brightness" max="100" min="0" value="80">
    </div>
    <div id="modes">
         <label for="none">
            None
            <input type="radio" class="${MODE_RADIO_BUTTONS_ID}" name="mode" value="0" checked>
         </label>
         <label for="wave">
            Wave
            <input type="radio" class="${MODE_RADIO_BUTTONS_ID}" name="mode" value="1">
         </label>
    </div>
  </div>
`
setupColorPicker();
setupBrightnessRange();
setupModeSelect();