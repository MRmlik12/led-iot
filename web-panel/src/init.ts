import iro from "@jaames/iro";
import { DIV_PICKER_ID } from "./consts.ts";
import { changeLedStripColor } from "./api/actions.ts";

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