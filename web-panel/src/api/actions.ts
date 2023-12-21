import { RgbModel } from "./models/rgbModel.ts";

export const changeLedStripColor = async (data: any) => {
    await fetch("/color", {
        body: data,
        method: "POST"
    })
}

export const changeLedStripMode = async (data: any) => {
    await fetch("mode", {
        body: data,
        method: "POST"
    })
}

export const getLedStripColor = async (): Promise<RgbModel | undefined> => {
    return await fetch("/currentRgb")
        .then(async (data) => {
            if (data.ok) {
                const json = await data.json();

                return json as RgbModel;
            }
        })
}