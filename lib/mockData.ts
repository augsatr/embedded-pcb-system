import { MandiPrice, Buyer, Lot, ForecastPoint } from "./types";

export const mandiPrices: MandiPrice[] = [
  { market: "Pune APMC", district: "Pune", commodity: "Onion", variety: "Red", modalPrice: 2850, minPrice: 2200, maxPrice: 3200, arrivalQty: 420, trend: "up", distanceKm: 12 },
  { market: "Nashik Lasalgaon", district: "Nashik", commodity: "Onion", variety: "Red", modalPrice: 2720, minPrice: 2100, maxPrice: 3050, arrivalQty: 890, trend: "stable", distanceKm: 45 },
  { market: "Nagpur Kalamna", district: "Nagpur", commodity: "Soybean", variety: "JS-335", modalPrice: 4650, minPrice: 4300, maxPrice: 4900, arrivalQty: 310, trend: "down", distanceKm: 8 },
  { market: "Kolhapur", district: "Kolhapur", commodity: "Tomato", variety: "Hybrid", modalPrice: 1800, minPrice: 1200, maxPrice: 2400, arrivalQty: 150, trend: "up", distanceKm: 22 },
  { market: "Aurangabad", district: "Chh.Sambhajinagar", commodity: "Cotton", variety: "Long Staple", modalPrice: 7200, minPrice: 6800, maxPrice: 7500, arrivalQty: 95, trend: "stable", distanceKm: 30 },
  { market: "Solapur", district: "Solapur", commodity: "Tur Dal", variety: "Bold", modalPrice: 9800, minPrice: 9200, maxPrice: 10500, arrivalQty: 60, trend: "up", distanceKm: 18 },
];

export const buyers: Buyer[] = [
  { id:"B1", name:"Sahyadri Farms Pvt Ltd", type:"Processor", commodity:"Onion", requiredQty:500, offerPrice:2950, qualityGrade:"A Grade >55mm", verified:true, rating:4.7, location:"Nashik" },
  { id:"B2", name:"Reliance Retail - Pune DC", type:"Retailer", commodity:"Tomato", requiredQty:200, offerPrice:2100, qualityGrade:"B Grade", verified:true, rating:4.5, location:"Pune" },
  { id:"B3", name:"MahaFPO Federation", type:"FPO", commodity:"Soybean", requiredQty:1000, offerPrice:4750, qualityGrade:"FAQ", verified:true, rating:4.8, location:"Nagpur" },
  { id:"B4", name:"VAP Agro Exports", type:"Exporter", commodity:"Onion", requiredQty:300, offerPrice:3100, qualityGrade:"Export Grade", verified:false, rating:4.1, location:"Mumbai APMC" },
  { id:"B5", name:"Mid-Day Meal Authority", type:"Institutional", commodity:"Tur Dal", requiredQty:800, offerPrice:10200, qualityGrade:"Agmark Grade 1", verified:true, rating:4.6, location:"Pune" },
];

export const lots: Lot[] = [
  { id:"LOT-1023", farmer:"Ramesh Pawar (FPO: Junnar)", commodity:"Onion", qty:12, grade:"A (55-70mm)", status:"Graded", priceAsk:2900 },
  { id:"LOT-1024", farmer:"Sunita More", commodity:"Tomato", qty:5, grade:"B", status:"Ready", priceAsk:1900 },
  { id:"LOT-1025", farmer:"FPO - Solapur Cluster (23 farmers)", commodity:"Tur Dal", qty:40, grade:"Agmark G1", status:"Listed", priceAsk:10000 },
];

export const onionForecast: ForecastPoint[] = [
  { date:"2026-07-20", price:2450, volume: 820 }, { date:"2026-07-27", price:2580, volume: 790 },
  { date:"2026-08-03", price:2720, volume: 710 }, { date:"2026-08-10", price:2850, volume: 420 },
  { date:"2026-08-17", price:2920, predicted:2920, volume: 380 }, { date:"2026-08-24", price:0, predicted:3050, volume: 350 },
  { date:"2026-08-31", price:0, predicted:3120, volume: 330 }, { date:"2026-09-07", price:0, predicted:2980, volume: 500 },
];

export const saleWindowAdvice = {
  commodity: "Onion",
  recommendation: "HOLD for 10-14 days",
  reason: "Modal price up 7.2% WoW in Pune/Nashik. Arrival volumes down 18%. Forecast peak around 31 Aug (₹3,120/q). Storage cost ₹45/q/week at NAFED warehouse (2km).",
  expectedGain: "+ ₹240/q (+8.4%) net of storage & transport",
  risk: "Medium - Monsoon arrival may increase late Aug",
};
