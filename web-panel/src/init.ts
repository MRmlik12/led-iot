import iro from "@jaames/iro";
import { BRIGHTNESS_RANGE_ID, DIV_PICKER_ID, MODE_RADIO_BUTTONS_ID } from "./consts.ts";
import { changeBrightness, changeLedStripColor, changeLedStripMode } from "./api/actions.ts";

export const setupColorPicker = () => {
    const colorPicker = iro.ColorPicker(`#${DIV_PICKER_ID}`, {
        width: innerWidth < 1000 ? innerWidth / 1.20 : innerWidth / 3,
        color: '#fff'
    });

    colorPicker.on('color:change', async (color: any) => {
        const json = JSON.stringify(color.rgb);
        await changeLedStripColor(json);
    })
}

export const setupModeSelect = () => {
    const elements = document.getElementsByClassName(MODE_RADIO_BUTTONS_ID) as HTMLCollectionOf<HTMLInputElement>;

    for (const element of elements) {
        element.addEventListener("click", async () => {
            console.log(element);
            const model = {
                mode: parseInt(element.value)
            }

            const json = JSON.stringify(model)
            await changeLedStripMode(json);
        })
    }
}

export const setupBrightnessRange = () => {
    const brightness = document.getElementById(BRIGHTNESS_RANGE_ID);

    brightness?.addEventListener("change", async (e) => {
        const target = (e as InputEvent).target;
        if (target == null) {
            return;
        }

        const level = parseInt((target as HTMLInputElement).value);
        const model = {
            level
        };

        await changeBrightness(JSON.stringify(model));
    });
}
