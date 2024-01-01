import { LedStripModel } from "./models/ledStripModel.ts";

const BASE_API_ENDPOINT = "/api"

export const changeLedStripState = async (data: any) => {
    await fetch(`${BASE_API_ENDPOINT}/update`, {
        body: data,
        method: "POST"
    })
}

export const getLedStripState = async (): Promise<LedStripModel | undefined> => {
    return await fetch(`${BASE_API_ENDPOINT}/current`)
        .then(async (data) => {
            if (data.ok) {
                const json = await data.json();

                return json as LedStripModel;
            }
        })
}