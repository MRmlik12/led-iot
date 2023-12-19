import './style.css'
import { setupColorPicker } from "./init.ts";
import { DIV_PICKER_ID } from './consts.ts';

document.querySelector<HTMLDivElement>('#app')!.innerHTML = `
  <div id="container">
    <h1 id="title">LED PANEL</h1>
    <div id="${DIV_PICKER_ID}"></div>
  </div>
`
setupColorPicker();
