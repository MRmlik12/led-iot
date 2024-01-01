import iro from "@jaames/iro";
import { BRIGHTNESS_RANGE_ID, DIV_PICKER_ID, MODE_RADIO_BUTTONS_ID } from "./consts.ts";
import { LedStripMode, LedStripModel } from "./api/models/ledStripModel.ts";
import { changeLedStripState } from "./api/actions.ts";
import { BehaviorSubject, fromEvent } from "rxjs";
import { IroColorPicker } from "@jaames/iro/dist/ColorPicker";

let colorPicker: IroColorPicker;
let brightnessElement: HTMLInputElement | null = null;
let modeElements: HTMLCollectionOf<HTMLInputElement> | null = null;

export const ledStripState = new BehaviorSubject<LedStripModel>({
    r: 0,
    g: 0,
    b: 0,
    mode: LedStripMode.NONE,
    brightness: 80
});

let initCompleted = false;
ledStripState.subscribe(async (model) => {
   if (model && initCompleted) {
       const json = JSON.stringify(model);
       await changeLedStripState(json);
   } else if (model && !initCompleted && colorPicker) {
       colorPicker.addColor(`rgb(${model.r}, ${model.g}, ${model.b})`, 0);
       changeModeValue(model.mode);
       changeBrightnessValue(model.brightness.toString());
       initCompleted = true;
   }
});

const changeModeValue = (mode: LedStripMode) => {
    const radio = document.getElementById(LedStripMode[mode].toLowerCase()) as HTMLInputElement;
    radio.checked = true;
}

const changeBrightnessValue = (val: string) => {
    brightnessElement!.value = val;
}

export const setupColorPicker = () => {
    colorPicker = iro.ColorPicker(`#${DIV_PICKER_ID}`, {
        width: innerWidth < 1000 ? innerWidth / 1.20 : innerWidth / 3,
        layout: [
            {
                component: iro.ui.Wheel
            }
        ],
        color: '#fff'
    });

    colorPicker.on('color:change', async (color: any) => {
        const modifiedModel = ledStripState.value!;

        modifiedModel.r = color.rgb.r;
        modifiedModel.g = color.rgb.g;
        modifiedModel.b = color.rgb.b;

        ledStripState.next(modifiedModel);
    })
}

export const setupModeSelectEvents = () => {
    modeElements = document.getElementsByClassName(MODE_RADIO_BUTTONS_ID) as HTMLCollectionOf<HTMLInputElement>;

    for (const element of modeElements) {
        element.addEventListener("click", async () => {
            const modifiedModel = ledStripState.value!;
            modifiedModel.mode = parseInt(element.value);

            ledStripState.next(modifiedModel);
        })
    }
}

export const setupBrightnessRangeEvents = () => {
    brightnessElement = document.getElementById(BRIGHTNESS_RANGE_ID) as HTMLInputElement;

    fromEvent(brightnessElement!, "change").subscribe(async (e) => {
        const target = (e as InputEvent).target;
        if (target == null) {
            return;
        }

        const level = parseInt((target as HTMLInputElement).value);
        const modifiedModel = ledStripState.value!;
        modifiedModel.brightness = level;

        ledStripState.next(modifiedModel);
    });
}
