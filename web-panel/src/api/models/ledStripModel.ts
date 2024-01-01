export interface LedStripModel {
    r: number;
    g: number;
    b: number;
    mode: LedStripMode;
    brightness: number;
}

export enum LedStripMode {
    NONE,
    WAVE
}