export type BacktestRow = { year: string; action: string; priceIfSoldNow: number; priceIfHeld: number; holdDays: number; storageCost: number; netGainPerQ: number; netPct: string; verdict: string; };
export const backtest: BacktestRow[] = [
  { year:"2023 (Aug 10-24)", action:"Held 13d", priceIfSoldNow:2580, priceIfHeld:2940, holdDays:13, storageCost:84, netGainPerQ:276, netPct:"+10.7%", verdict:"✓ Win" },
  { year:"2024 (Aug 12-26)", action:"Held 9d", priceIfSoldNow:2720, priceIfHeld:2985, holdDays:9, storageCost:58, netGainPerQ:207, netPct:"+7.6%", verdict:"✓ Win" },
  { year:"2025 (Aug 10-22)", action:"Sold Now (rain)", priceIfSoldNow:2850, priceIfHeld:2710, holdDays:0, storageCost:0, netGainPerQ:0, netPct:"Avoided -4.9% loss", verdict:"✓ Saved" },
  { year:"Avg 2023-25", action:"Follow advisor", priceIfSoldNow:2717, priceIfHeld:2878, holdDays:7.3, storageCost:47, netGainPerQ:161, netPct:"+6.2%", verdict:"Mean" },
];

export const impactNow = {
  todayVs3Days: { ifSellToday: 2850, ifWait3Days: 2920, gain3d: 70, netAfterStorage19: 51, pct:" +1.8% net" },
  ifWaitPeak: { waitDays:12, peak:3120, netGain:240, pct:"+8.4%", totalOn12MT:"₹28,800 extra on 12 MT lot = 19 days of farm labour" },
  fpoPool: { size:"23 farmers → 40 MT pooled", premium:"+₹110/q bulk premium", logisticsSavings:"₹43/q saved (shared truck)", totalBenefit:"₹3.24L collective gain vs solo sale (Aug 2025 pilot, Solapur)" },
  lossesAvoided: { postHarvestLoss:"From 14% → 6% with storage prompt", distressSale:"-38% distress sales when hold advice + warehouse within 5km" }
};
