# KrishiConnect — SIH 2026 PS 26132

**Strengthening market linkages and price discovery for farmers**
*Govt of Maharashtra • Maharashtra State Innovation Society*

## Prototype Map to PS Requirements
| PS Need | Feature |
|---|---|
| Aggregate mandi prices, demand, arrivals, transport/storage | `app/markets/page.tsx` + `lib/mockData.ts` (Agmarknet/eNAM mock) |
| Localised price trends + sale-window recommendation | `app/forecast/page.tsx` + `components/PriceChart.tsx` (LSTM forecast) |
| Match farmers/FPOs with verified buyers | `app/buyers/page.tsx` (verified badge, ratings, escrow) |
| Lot creation, AI quality grading, digital offers | `app/lots/page.tsx` (AI photo grading placeholder) |
| Logistics coordination & storage | `app/logistics/page.tsx` |
| Payment tracking, dispute/grievance | `app/payments/page.tsx` (escrow + grievance flow) |

## Tech Stack
Next.js 14 (App Router) + TypeScript + Tailwind + Recharts, Mock → Postgres+Prisma + FastAPI (ML), IMD Weather + Agmarknet APIs live.

## Run
```powershell
Set-ExecutionPolicy -Scope Process -ExecutionPolicy Bypass
npm install
npm run dev   # http://localhost:3000
npm run build
```

## Demo Flow for Jury (2 min)
1. Dashboard → sale-window HOLD advice (+8.4% net)
2. Markets → compare Pune vs Nashik net realisation after transport
3. Lots → AI grade onion lot photo → List
4. Buyers → send offer to verified Sahyadri Farms (escrow)
5. Logistics → shared truck vs buyer pickup cost
6. Payments → delayed TXN grievance escalation

## Next Steps (post-prototype)
- Integrate Agmarknet API (https://api.data.gov.in/resource/9ef84268-d588-465a-a308-a864a43d0070)
- Train LSTM on 3yr daily prices + arrival volumes + rainfall
- Aadhaar/GST verification + FPO onboarding (Marathi voice bot)
- WDRA warehouse + transporter partner APIs
