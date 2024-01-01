import './style.css'
import { ledStripState, setupBrightnessRangeEvents, setupColorPicker, setupModeSelectEvents } from "./init.ts";
import { BRIGHTNESS_RANGE_ID, DIV_PICKER_ID, MODE_RADIO_BUTTONS_ID } from './consts.ts';
import { getLedStripState } from "./api/actions.ts";
import { fromEvent } from "rxjs";

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
            <input id="none" type="radio" class="${MODE_RADIO_BUTTONS_ID}" name="mode" value="0" checked>
         </label>
         <label for="wave">
            Wave
            <input id="wave" type="radio" class="${MODE_RADIO_BUTTONS_ID}" name="mode" value="1">
         </label>
    </div>
  </div>
`

fromEvent(document, 'DOMContentLoaded').subscribe(async () => {
    setupColorPicker();
    setupBrightnessRangeEvents();
    setupModeSelectEvents();

    const response = await getLedStripState();

    if (response) {
        ledStripState.next(response);
    }
});